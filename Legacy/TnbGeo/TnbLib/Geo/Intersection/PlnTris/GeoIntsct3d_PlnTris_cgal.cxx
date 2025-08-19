// ReSharper disable CppClangTidyClangDiagnosticLanguageExtensionToken
#include <GeoIntsct3d_PlnTris.hxx>

#include <Entity3d_Triangulation.hxx>
//#include <Entity3d_Triangle.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/gp_Pln.hxx>

#ifdef Handle
#undef Handle
#endif // Handle
#include <boost/optional/optional.hpp>
#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\Simple_cartesian.h>
#include <CGAL\AABB_face_graph_triangle_primitive.h>
#include <CGAL\Surface_mesh.h>
#include <CGAL\AABB_tree.h>
#include <CGAL\AABB_traits.h>
#include <CGAL\Segment_3.h>
#include <CGAL\Polygon_2.h>
#include <CGAL\Plane_3.h>
#include <CGAL\Triangle_3.h>
//#include <CGAL\intersections.h>
#include <CGAL\Polyhedron_3.h>

#include <CGAL\Polygon_mesh_processing\stitch_borders.h>

//typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Simple_cartesian<double> Kernel;

//namespace plnTrisLib
//{
//	static Kernel cgal_object;
//}

typedef Kernel::Point_3 Point_3;
typedef Kernel::Segment_3 Segment_3;
typedef Kernel::Plane_3 Plane_3;
typedef Kernel::Vector_3 Vector_3;
typedef Kernel::Triangle_3 Triangle_3;
//typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef CGAL::Surface_mesh<Point_3> SurfaceMesh;
typedef CGAL::AABB_face_graph_triangle_primitive<SurfaceMesh> Primitive;
typedef CGAL::AABB_traits<Kernel, Primitive> Traits;
typedef CGAL::AABB_tree<Traits> Tree;


typedef boost::optional< Tree::Intersection_and_primitive_id<Plane_3>::Type > Plane_intersection;

namespace tnbLib
{
	namespace
	{
		auto get_point = [](const Point_3& thePt)-> Pnt3d
			{
				return { thePt.x(), thePt.y(), thePt.z() };
			};
	}
}

std::vector<std::shared_ptr<tnbLib::GeoIntsct3d_PlnTris::intsctEntity>>
tnbLib::GeoIntsct3d_PlnTris::CalcIntersections
(
	const gp_Pln& thePlane,
	const Entity3d_Triangulation& theTris
)
{
	SurfaceMesh surfMesh;
	std::vector<SurfaceMesh::Vertex_index> ids;
	for (const auto& p : theTris.Points())
	{
		auto [x, y, z] = p.Components();
		auto id = surfMesh.add_vertex(Point_3(x, y, z));
		ids.push_back(id);
	}
	for (const auto& x : theTris.Connectivity())
	{
		auto v0 = x.Value(0);
		auto v1 = x.Value(1);
		auto v2 = x.Value(2);

		surfMesh.add_face(ids.at(Index_Of(v0)), ids.at(Index_Of(v1)), ids.at(Index_Of(v2)));
	}
	CGAL::Polygon_mesh_processing::stitch_borders(surfMesh);
	// constructs plane query
	Standard_Real a, b, c, d;
	thePlane.Coefficients(a, b, c, d);
	Plane_3 plane(a, b, c, d);

	// constructs AABB tree
	Tree tree(surfMesh.faces_begin(), surfMesh.faces_end(), surfMesh);

	std::list<Plane_intersection> primitives;
	tree.all_intersections(plane, std::back_inserter(primitives));

	std::vector<std::shared_ptr<intsctEntity>> entities;
	entities.reserve(primitives.size());

	for (const auto& x : primitives)
	{
		if (auto pt = std::get_if<Point_3>(&(x->first)))
		{
			entities.push_back(std::make_shared<pntIntsct>(get_point(*pt)));
		}
		else if (auto seg = std::get_if<Segment_3>(&(x->first)))
		{
			auto ent = std::make_shared<segIntsct>
				(
					std::array<Pnt3d, 2>{ get_point(seg->vertex(0)), get_point(seg->vertex(1)) });

			entities.push_back(std::move(ent));
		}
		else if (auto tri = std::get_if<Triangle_3>(&(x->first)))
		{
			auto ent = std::make_shared<triIntsct>
				(
					std::array<Pnt3d, 3>{ get_point(tri->vertex(0)), get_point(tri->vertex(1)), get_point(tri->vertex(2)) });

			entities.push_back(std::move(ent));
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "undefined type of intersection has been detected." << endl
				<< abort(FatalError);
		}
	}
	return entities;
}