#include <VoyageGeo_Path2.hxx>

#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::Entity2d_Polygon>> 
tnbLib::VoyageGeo_Path2::RetrieveOffsets() const
{
	std::vector<std::shared_ptr<Entity2d_Polygon>> polygons;
	for (const auto& x : Curves())
	{
		Debug_Null_Pointer(x);
		const auto& mesh = x->Mesh();
		polygons.push_back(mesh);
	}
	return std::move(polygons);
}