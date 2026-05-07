#include <PtdModel_Profile.hxx>

#include <Geo_AffineTrsf_PtsToUnitSq.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <StdFail_NotDone.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>

tnbLib::PtdModel_Profile::PtdModel_Profile
(
	const Standard_Integer theIndex,
	const word & theName
)
	: PtdModel_Entity(theIndex, theName)
{
	//- empty body
}

tnbLib::PtdModel_Profile::PtdModel_Profile
(
	const Handle(Geom2d_Curve)& c,
	const std::shared_ptr<geoLib::AffineTrsf_PtsToUnitSqObj>& theTrsf
)
	: theGeometry_(c)
	, theTrsf_(theTrsf)
{
	//- empty body
}

tnbLib::PtdModel_Profile::PtdModel_Profile
(
	Handle(Geom2d_Curve) && c,
	std::shared_ptr<geoLib::AffineTrsf_PtsToUnitSqObj>&& theTrsf
)
	: theGeometry_(std::move(c))
	, theTrsf_(std::move(theTrsf))
{
	//- empty body
}


std::vector<Standard_Real>
tnbLib::PtdModel_Profile::RetrieveValues
(
	const std::vector<Standard_Real>& xs
) const
{
	if (NOT Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometry curve has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Trsf())
	{
		FatalErrorIn(FunctionSIG)
			<< "no transformation object has been loaded!" << endl
			<< abort(FatalError);
	}
	std::vector<Standard_Real> values;
	values.reserve(xs.size());

	auto pt0 = Geometry()->Value(Geometry()->FirstParameter());
	auto pt1 = Geometry()->Value(Geometry()->LastParameter());

	values.push_back(Trsf()->CalcInvY(pt0.Y()));

	for (size_t i = 1; i < xs.size() - 1; i++)
	{
		auto x = Trsf()->CalcTrsfX(xs[i]);
		Handle(Geom2d_Line) line = new Geom2d_Line(gp_Pnt2d(x, 0), gp_Dir2d(0, 1));

		Geom2dAPI_InterCurveCurve alg;
		alg.Init(Geometry(), line, 1.0E-4);

		if (NOT alg.NbPoints())
		{
			FatalErrorIn(FunctionSIG)
				<< "no intersection point has been found!" << endl
				<< " - x: " << x << endl
				<< " - x0: " 
				<< Geometry()->Value(Geometry()->FirstParameter()) 
				<< ", x1: " 
				<< Geometry()->Value(Geometry()->LastParameter()) 
				<< endl
				<< abort(FatalError);
		}

		if (alg.NbPoints() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid profile has been found!" << endl
				<< abort(FatalError);
		}

		auto pt = alg.Point(1);
		values.push_back(Trsf()->CalcInvY(pt.Y()));
	}

	values.push_back(Trsf()->CalcInvY(pt1.Y()));
	return std::move(values);
}

std::shared_ptr<tnbLib::PtdModel_Profile>
tnbLib::PtdModel_Profile::MakeProfile
(
	const TColgp_Array1OfPnt2d & thePoles,
	const TColStd_Array1OfReal & theWeights,
	const TColStd_Array1OfReal & theKnots,
	const TColStd_Array1OfInteger & theMults,
	const Standard_Integer theDegree
)
{
	std::vector<Pnt2d> Qs;
	Qs.reserve(thePoles.Size() + 1);
	for (Standard_Integer k = 1; k <= thePoles.Size(); k++)
	{
		Qs.push_back(thePoles.Value(k));
	}

	auto trsf = std::make_shared<geoLib::AffineTrsf_PtsToUnitSq>(Qs);
	Debug_Null_Pointer(trsf);

	trsf->Perform();
	Debug_If_Condition_Message(NOT trsf->IsDone(), "the algorithm is not performed!");

	auto tQs = trsf->CalcTrsfPoints(Qs);

	TColgp_Array1OfPnt2d poles(1, thePoles.Size());
	Standard_Integer k = 0;
	for (const auto& x : tQs)
	{
		poles.SetValue(++k, x);
	}

	auto trsfObj = std::make_shared<geoLib::AffineTrsf_PtsToUnitSqObj>(trsf->TrsfObj());
	Debug_Null_Pointer(trsfObj);

	try
	{
		Handle(Geom2d_Curve) c = new Geom2d_BSplineCurve(poles, theWeights, theKnots, theMults, theDegree);
		auto profile = std::make_shared<PtdModel_Profile>(std::move(c), std::move(trsfObj));
		return std::move(profile);
	}
	catch (const StdFail_NotDone&)
	{
		FatalErrorIn(FunctionSIG)
			<< "opencascade threw an exception: unable to create the curve!" << endl
			<< abort(FatalError);
	}
	return nullptr;
}