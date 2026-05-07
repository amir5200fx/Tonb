#include <GeoSlicer3d_PlnTris.hxx>

#include <Geo_Tools.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/gp_Pln.hxx>

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

#include <CGAL\Polygon_mesh_slicer.h>
#include <CGAL\Polygon_mesh_processing\clip.h>
//#include <CGAL\Polygon_mesh_processing\split.h>
#include <CGAL\Polygon_mesh_processing\stitch_borders.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel   Kernel;
typedef CGAL::Surface_mesh<Kernel::Point_3>                   SurfMesh;

typedef Kernel::Point_3										  Point_3;
typedef std::vector<Kernel::Point_3>                          Polyline_type;
typedef std::list<Polyline_type>                              Polylines;

typedef Kernel::Plane_3 Plane_3;

typedef CGAL::AABB_halfedge_graph_segment_primitive<SurfMesh>      HGSP;
typedef CGAL::AABB_traits<Kernel, HGSP>                            AABB_traits;
typedef CGAL::AABB_tree<AABB_traits>							   AABB_tree;



void tnbLib::GeoSlicer3d_PlnTris::Perform()
{
	if (NOT Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< "no plane has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been loaded." << endl
			<< abort(FatalError);
	}

	static auto getPoint = [](const Point_3& thePt)
	{
		Pnt3d pt(thePt.x(), thePt.y(), thePt.z());
		return std::move(pt);
	};

	SurfMesh surfMesh;
	std::vector<SurfMesh::Vertex_index> ids;
	for (const auto& p : Mesh()->Points())
	{
		auto [x, y, z] = p.Components();
		auto id = surfMesh.add_vertex(Point_3(x, y, z));
		ids.push_back(id);
	}
	for (const auto& x : Mesh()->Connectivity())
	{
		auto v0 = x.Value(0);
		auto v1 = x.Value(1);
		auto v2 = x.Value(2);

		surfMesh.add_face(ids.at(Index_Of(v0)), ids.at(Index_Of(v1)), ids.at(Index_Of(v2)));
	}
	CGAL::Polygon_mesh_processing::stitch_borders(surfMesh);

	{ // left side [2/17/2023 Payvand]
		auto [a, b, c, d] = Geo_Tools::GetCoefficients(*Plane());
		Plane_3 plane(a, b, c, d);

		if (CGAL::Polygon_mesh_processing::clip(surfMesh, plane))
		{
			auto mesh = std::make_shared<Entity3d_Triangulation>();
			auto& pts = mesh->Points();
			std::map<Standard_Integer, Standard_Integer> vtx_indx;
			Standard_Integer i = 0;
			for (const auto& v : surfMesh.vertices())
			{
				auto paired = std::make_pair(v, ++i);
				vtx_indx.insert(std::move(paired));
				const auto& x = surfMesh.point(v);
				Pnt3d pt(x.x(), x.y(), x.z());
				pts.push_back(std::move(pt));
			}

			auto& ids = mesh->Connectivity();
			std::vector<std::pair<Standard_Integer, Standard_Integer>> indx_index;
			Standard_Integer indx = 0;
			for (const auto& fi : surfMesh.faces())
			{
				auto hf = surfMesh.halfedge(fi);
				connectivity::triple t;
				Standard_Integer k = 0;
				for (auto hi : halfedges_around_face(hf, surfMesh))
				{
					auto vi = target(hi, surfMesh);
					Debug_Bad_Index(k, 0, 2);
					t.Value(k++) = vtx_indx.at(vi);

				}
				ids.push_back(std::move(t));
			}
			theClipped_ = std::move(mesh);
		}
	}
	Change_IsDone() = Standard_True;

	// AABB Slicer constructor from the cutted mesh
	/*AABB_tree tree(edges(surfMesh).first, edges(surfMesh).second, surfMesh);

	Polylines polylines;
	CGAL::Polygon_mesh_slicer<SurfMesh, Kernel> slicer(surfMesh, tree);

	slicer(plane, std::back_inserter(polylines));
	std::cout << "size = " << polylines.size() << std::endl;
	int i = 0;
	for (const auto& x : polylines)
	{
		std::cout << " - i : " << ++i << ", size: " << x.size() << std::endl;
	}*/
}

//Import off files and instantiate meshes
//const char* filename1 = "test.off";
//const char* filename2 = "cutMesh2.off";
//std::ifstream input(filename1);
//Mesh cuttedMesh, cutMesh;
//if (!input || !(input >> cuttedMesh))
//{
//	std::cerr << "First mesh is not a valid off file." << std::endl;
//	return 0;
//}
//input.close();
//input.open(filename2);
//if (!input || !(input >> cutMesh))
//{
//	std::cerr << "Second mesh is not a valid off file." << std::endl;
//	return 0;
//}
//input.close();
//// AABB Slicer constructor from the cutted mesh
//AABB_tree tree(edges(cuttedMesh).first, edges(cuttedMesh).second, cuttedMesh);
//tree.accelerate_distance_queries();
//CGAL::Polygon_mesh_slicer<Mesh, K> slicer_aabb(cuttedMesh, tree);
//
//std::cout << cutMesh.num_vertices() << std::endl;
//// For each face of the cut mesh
//BOOST_FOREACH(face_descriptor f, faces(cutMesh))
//{
//	std::cout << "Face " << f << std::endl;
//	Point points[3];
//	int i = 0;
//	//for each point of the current face
//	BOOST_FOREACH(vertex_descriptor v, CGAL::vertices_around_face(cutMesh.halfedge(f), cutMesh))
//	{
//		points[i] = cutMesh.point(v);
//		++i;
//	}
//	Polylines polylines;
//	// Perform the slice between the current face of the cut mesh and the cutted mesh
//	slicer_aabb(K::Plane_3(points[0], points[1], points[2]), std::back_inserter(polylines));
//	std::cout << "the slicer intersects " << polylines.size() << " polylines" << std::endl;
//
//	//for each polyline computed by this face of the cutmesh
//	BOOST_FOREACH(Polyline_type polyline, polylines)
//	{
//		std::cout << "Polyline : " << polyline.size() << " points" << std::endl;
//
//		BOOST_FOREACH(Point point, polyline)
//		{
//			std::cout << "Point : " << point << std::endl;
//		}
//	}
//	std::cout << std::endl;
//	polylines.clear();
//}