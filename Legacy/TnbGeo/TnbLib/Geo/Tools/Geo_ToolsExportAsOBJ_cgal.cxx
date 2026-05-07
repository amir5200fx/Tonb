#include <Geo_Tools.hxx>

#include <Entity3d_Triangulation.hxx>

#ifdef Handle
#undef Handle
#endif // Handle

#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\Simple_cartesian.h>
#include <CGAL\AABB_halfedge_graph_segment_primitive.h>
#include <CGAL\Surface_mesh.h>
#include <CGAL\AABB_tree.h>
#include <CGAL\AABB_traits.h>
#include <CGAL\Plane_3.h>

#include <CGAL\Polygon_mesh_processing\stitch_borders.h>
#include <CGAL\Surface_mesh\IO\OFF.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel   Kernel;
typedef CGAL::Surface_mesh<Kernel::Point_3>                   SurfMesh;

typedef Kernel::Point_3										  Point_3;

void tnbLib::Geo_Tools::ExportAsOBJ_cgal
(
	const Entity3d_Triangulation& theTriangulation,
	std::ostream& theFile
)
{
	SurfMesh surfMesh;
	std::vector<SurfMesh::Vertex_index> ids;
	for (const auto& p : theTriangulation.Points())
	{
		auto [x, y, z] = p.Components();
		auto id = surfMesh.add_vertex(Point_3(x, y, z));
		ids.push_back(id);
	}
	for (const auto& x : theTriangulation.Connectivity())
	{
		auto v0 = x.Value(0);
		auto v1 = x.Value(1);
		auto v2 = x.Value(2);

		surfMesh.add_face(ids.at(Index_Of(v0)), ids.at(Index_Of(v1)), ids.at(Index_Of(v2)));
	}

	CGAL::Polygon_mesh_processing::stitch_borders(surfMesh);
	if (NOT CGAL::IO::write_OBJ(theFile, surfMesh))
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to export the mesh." << endl
			<< abort(FatalError);
	}
}