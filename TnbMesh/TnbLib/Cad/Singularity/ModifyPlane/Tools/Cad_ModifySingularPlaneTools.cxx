#include <Cad_ModifySingularPlaneTools.hxx>

#include <Aft2d_gPlnCurveSurface.hxx>
#include <Aft2d_gRegionPlaneSurface.hxx>
#include <Aft2d_gPlnWireSurface.hxx>
#include <Cad_gApprxPlnWireSurface.hxx>
#include <GModel_ParaCurve.hxx>
#include <TModel_ParaCurve.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Precision.hxx>

template<>
std::pair
<
	std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>, 
	std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>
>
tnbLib::Cad_ModifySingularPlaneTools<tnbLib::Aft2d_gRegionPlaneSurface>::Split
(
	const Standard_Real x, 
	const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	const auto& curve = theCurve->Curve();
	Debug_Null_Pointer(curve);

	auto[c0, c1] = GModel_ParaCurve::Split(x, curve);
	if (NOT c0)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is null" << endl
			<< abort(FatalError);
	}
	if (NOT c1)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is null" << endl
			<< abort(FatalError);
	}
	auto C0 = std::make_shared<Aft2d_gPlnCurveSurface>(std::move(c0));
	auto C1 = std::make_shared<Aft2d_gPlnCurveSurface>(std::move(c1));
	auto t = std::make_pair(std::move(C0), std::move(C1));
	return std::move(t);
}

template<>
std::shared_ptr<tnbLib::Entity2d_Polygon> 
tnbLib::Cad_ModifySingularPlaneTools<tnbLib::Aft2d_gRegionPlaneSurface>::GetPolygon
(
	const std::shared_ptr<Aft2d_gPlnWireSurface>& theWire,
	const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
)
{
	Debug_Null_Pointer(theWire);
	Debug_Null_Pointer(theInfo);
	const auto& curves = theWire->Curves();
	
	auto alg = std::make_shared<Cad_gApprxPlnWireSurface>(theWire, theInfo);
	Debug_Null_Pointer(alg);

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");

	const auto& polygons = alg->Polygons();
	Pln_Tools::WatertightWire(polygons);

	auto wire = Pln_Tools::MergeApproxWire(polygons, Precision::PConfusion());
	return std::move(wire);
}
