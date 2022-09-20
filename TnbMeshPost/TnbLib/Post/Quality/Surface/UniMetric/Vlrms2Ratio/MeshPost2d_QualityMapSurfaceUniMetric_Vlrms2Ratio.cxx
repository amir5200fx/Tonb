#include <MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio.hxx>

#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <Aft2d_ElementSurface.hxx>
#include <Geo_MetricFunction.hxx>
#include <Geo2d_TriangleQualityTools.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Surface.hxx>

Standard_Real 
tnbLib::MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio::CalcQuality
(
	const Aft2d_ElementSurface & theElement
) const
{
	Debug_Null_Pointer(Metrics());
	const auto& geom = Metrics()->Geometry();
	Debug_Null_Pointer(geom);

	const auto& n0 = theElement.Node0();
	const auto& n1 = theElement.Node1();
	const auto& n2 = theElement.Node2();

	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);

	auto[x0, y0] = n0->Coord().Components();
	auto[x1, y1] = n1->Coord().Components();
	auto[x2, y2] = n2->Coord().Components();

	Pnt3d p0 = geom->Value(x0, y0);
	Pnt3d p1 = geom->Value(x1, y1);
	Pnt3d p2 = geom->Value(x2, y2);

	/*const auto& p0 = n0->Coord3D();
	const auto& p1 = n1->Coord3D();
	const auto& p2 = n2->Coord3D();*/

	Entity_Triangle<const Pnt3d &> t3(p0, p1, p2);
	auto t2 = Geo_Tools::CalcParametricTriangle(t3);

	return Geo2d_TriangleQualityTools::Vlrms2Ratio(t2.P0(), t2.P1(), t2.P2());
}