#include <MeshPost2d_QualityMap_Vlrms2Ratio.hxx>

#include <Aft2d_MetricPrcsr.hxx>
#include <Aft2d_Element.hxx>
#include <Geo2d_TriangleQualityTools.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real
tnbLib::MeshPost2d_QualityMap_Vlrms2Ratio::CalcQuality
(
	const Aft2d_Element& theElement
) const
{
	Debug_Null_Pointer(Metrics());
	Debug_Null_Pointer(geom);

	const auto& n0 = theElement.Node0();
	const auto& n1 = theElement.Node1();
	const auto& n2 = theElement.Node2();

	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);

	return Geo2d_TriangleQualityTools::Vlrms2Ratio
	(n0->Coord(), n1->Coord(), n2->Coord());
}