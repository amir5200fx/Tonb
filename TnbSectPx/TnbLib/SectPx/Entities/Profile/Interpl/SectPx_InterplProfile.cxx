#include <SectPx_InterplProfile.hxx>

#include <Pln_CurveTools.hxx>
#include <SectPx_Cloud.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_FixedKnots.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_BSplineCurve.hxx>

void tnbLib::SectPx_InterplProfile::Update() const
{
	auto cloud = Cloud().lock();
	if (NOT cloud)
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no cloud to construct an interpolation profile" << endl
			<< abort(FatalError);
	}

	auto curve =
		Handle(Geom2d_BSplineCurve)::DownCast
		(
			Pln_CurveTools::Interpolation(cloud->GetProfile()->Coords, Standard_False, theTol_)
		);
	if (NOT curve)
	{
		FatalErrorIn(FunctionSIG)
			<< "null curve has been encountered!" << endl
			<< abort(FatalError);
	}

	auto poles = RetrievePoles(*curve);
	auto knots = RetrieveKnots(*curve);

	size_t k = 0;
	for (const auto& x : Pnts())
	{
		auto pnt = x.lock();
		Debug_Null_Pointer(pnt);

		auto offset = std::dynamic_pointer_cast<sectPxLib::Pnt_Offset>(pnt);
		Debug_Null_Pointer(offset);

		offset->SetX(poles[k].X());
		offset->SetY(poles[k].Y());

		++k;
	}

	auto alg = std::dynamic_pointer_cast<SectPx_FixedKnots>(Knots());
	Debug_Null_Pointer(alg);

	alg->KnotsRef() = std::move(knots);
}

std::vector<Standard_Real> 
tnbLib::SectPx_InterplProfile::RetrieveKnots
(
	const Geom2d_BSplineCurve & curve
)
{
	const auto& knotSq = curve.KnotSequence();
	std::vector<Standard_Real> knots;
	knots.reserve(knotSq.Size());
	for (Standard_Integer i = 1; i <= knotSq.Size(); i++)
	{
		knots.push_back(knotSq.Value(i));
	}
	return std::move(knots);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::SectPx_InterplProfile::RetrievePoles
(
	const Geom2d_BSplineCurve & curve
)
{
	const auto& poles = curve.Poles();
	std::vector<Pnt2d> coords;
	coords.reserve(poles.Size());
	for (size_t i = 1; i <= poles.Size(); i++)
	{
		coords.push_back(poles.Value(i));
	}
	return std::move(coords);
}

const char* tnbLib::SectPx_InterplProfile::typeName_ = "interpolation profile";

tnbLib::word 
tnbLib::SectPx_InterplProfile::RegObjTypeName() const
{
	return typeName_;
}

std::shared_ptr<tnbLib::SectPx_InterplProfile> 
tnbLib::SectPx_InterplProfile::MakeProfile
(
	const std::shared_ptr<SectPx_Cloud>& theCloud,
	const std::shared_ptr<SectPx_FrameRegistry>& theReg,
	const Standard_Real tol
)
{
	Debug_Null_Pointer(theCloud);
	Debug_Null_Pointer(theCloud->GetProfile());

	auto curve = 
		Handle(Geom2d_BSplineCurve)::DownCast
		(
			Pln_CurveTools::Interpolation(theCloud->GetProfile()->Coords, Standard_False, tol)
		);
	if (NOT curve)
	{
		FatalErrorIn(FunctionSIG)
			<< "null curve has been encountered!" << endl
			<< abort(FatalError);
	}

	auto poles = RetrievePoles(*curve);
	auto knots = RetrieveKnots(*curve);

	auto pnts = SectPx_PntTools::MakeOffsetPnts(theCloud->GetProfile()->Coords, theReg);

	auto nodeMaker = std::make_shared<maker::Node>(theReg);
	Debug_Null_Pointer(nodeMaker);

	const auto n0_id = nodeMaker->CreateNode(pnts[0]);
	const auto n1_id = nodeMaker->CreateNode(pnts[pnts.size() - 1]);

	const auto n0 = nodeMaker->SelectNode(n0_id);
	Debug_Null_Pointer(n0);

	const auto n1 = nodeMaker->SelectNode(n1_id);
	Debug_Null_Pointer(n1);

	auto profile = std::make_shared<SectPx_InterplProfile>(n0, n1);
	Debug_Null_Pointer(profile);

	profile->SetCloud(theCloud);

	SetProfile(n0, std::dynamic_pointer_cast<SectPx_TopoProfile>(profile->This()));
	SetProfile(n1, std::dynamic_pointer_cast<SectPx_TopoProfile>(profile->This()));

	const auto interfaceMaker = std::make_shared<maker::Interface>(theReg);
	Debug_Null_Pointer(interfaceMaker);

	interfaceMaker->CreateEmpty(n0);
	interfaceMaker->CreateEmpty(n1);

	// remove this stupid knotAlg from profile structure
	/*auto knotAlg = std::make_shared<SectPx_FixedKnots>(std::move(knots));
	Debug_Null_Pointer(knotAlg);

	profile->SetKnot(std::move(knotAlg));*/

	std::vector<std::weak_ptr<SectPx_Pnt>> wPnts;
	wPnts.reserve(pnts.size());
	for (const auto& x : pnts)
	{
		Debug_Null_Pointer(x);
		wPnts.push_back(x);
	}

	profile->SetPnts(std::move(wPnts));

	return std::move(profile);
}