#include <Cad_ModifySingularPlaneTools.hxx>

#include <Cad_gApprxParaWire.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Precision.hxx>

template<>
std::shared_ptr<tnbLib::Entity2d_Polygon> 
tnbLib::Cad_ModifySingularPlaneTools<tnbLib::GModel_Plane>::GetPolygon
(
	const std::shared_ptr<GModel_ParaWire>& theWire,
	const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
)
{
	Debug_Null_Pointer(theWire);
	Debug_Null_Pointer(theInfo);
	const auto& curves = theWire->Curves();
	
	auto alg = std::make_shared<Cad_gApprxParaWire>(theWire, theInfo);
	Debug_Null_Pointer(alg);

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");

	const auto& polygons = alg->Polygons();
	Pln_Tools::WatertightWire(polygons);

	auto wire = Pln_Tools::MergeApproxWire(polygons, Precision::PConfusion());
	return std::move(wire);
}
