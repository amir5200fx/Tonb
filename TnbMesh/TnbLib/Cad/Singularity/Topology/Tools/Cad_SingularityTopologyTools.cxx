#include <Cad_SingularityTopologyTools.hxx>

#include <Aft2d_gPlnCurveSurface.hxx>
#include <Aft2d_gPlnWireSurface.hxx>
#include <Pln_Tools.hxx>
#include <Entity2d_Chain.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

template<>
std::shared_ptr<std::vector<std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>>>
tnbLib::Cad_SingularityTopologyTools::RetrieveCurves<tnbLib::Aft2d_gPlnCurveSurface, tnbLib::Aft2d_gPlnWireSurface>
(
	const std::shared_ptr<Aft2d_gPlnWireSurface>& theWire
	)
{
	Debug_Null_Pointer(theWire);
	auto curves = theWire->Curves();
	auto t = std::make_shared<std::vector<std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>>>(std::move(curves));
	return std::move(t);
}

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Cad_SingularityTopologyTools::GetChain
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	auto chain = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	pts.reserve(2);
	pts.push_back(theP0);
	pts.push_back(theP1);

	auto& indices = chain->Connectivity();
	indices.reserve(1);
	indices[0].Value(0) = 1;
	indices[0].Value(1) = 2;

	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Cad_SingularityTopologyTools::GetChain(const Handle(Geom2d_Curve)& theCurve)
{
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}

	auto chain = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	pts.reserve(2);
	pts.push_back(theCurve->Value(theCurve->FirstParameter()));
	pts.push_back(theCurve->Value(theCurve->LastParameter()));

	auto& indices = chain->Connectivity();
	indices.resize(1);
	indices[0].Value(0) = 1;
	indices[0].Value(1) = 2;

	return std::move(chain);
}

std::pair<std::shared_ptr<tnbLib::Entity2d_Chain>, std::shared_ptr<tnbLib::Entity2d_Chain>> 
tnbLib::Cad_SingularityTopologyTools::Split
(
	const Entity2d_Chain & theChain,
	const Pnt2d & thePt
)
{
	const auto& pts = theChain.Points();

	auto ch0 = GetChain(pts.at(0), thePt);
	auto ch1 = GetChain(thePt, pts.at(pts.size() - 1));
	auto t = std::make_pair(std::move(ch0), std::move(ch1));
	return std::move(t);
}

std::vector<std::shared_ptr<tnbLib::Entity2d_Chain>> 
tnbLib::Cad_SingularityTopologyTools::Split
(
	const Entity2d_Chain & theChain, 
	const std::vector<Pnt2d>& theCoords
)
{
	std::vector<std::shared_ptr<Entity2d_Chain>> chains;
	chains.reserve(theCoords.size() + 1);

	const auto& pts = theChain.Points();
	std::shared_ptr<Entity2d_Chain> gright;
	for (const auto& x : pts)
	{
		auto[left, right] = Split(theChain, x);
		gright = right;

		chains.push_back(std::move(left));
	}
	chains.push_back(std::move(gright));
	return std::move(chains);
}