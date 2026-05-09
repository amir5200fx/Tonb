//#include <Geo_Tools.hxx>
//
//#include <Entity3d_Triangulation.hxx>
//
//#ifdef Handle
//#undef Handle
//#endif // Handle
//
//#ifdef DebugInfo
//#undef DebugInfo
//#endif // DebugInfo
//
//
//#define CGAL_EIGEN3_ENABLED
//
//#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
//#include <CGAL\Polyhedron_3.h>
//#include <CGAL\poisson_surface_reconstruction.h>
//#include <CGAL\Poisson_reconstruction_function.h>
//#include <CGAL\compute_average_spacing.h>
//#include <CGAL\Surface_mesh.h>
//#include <CGAL\Polygon_mesh_processing\stitch_borders.h>
//#include <CGAL\Polygon_mesh_processing\compute_normal.h>
//#include <CGAL\grid_simplify_point_set.h>
//#include <CGAL\Point_set_3.h>
//#include <CGAL\jet_estimate_normals.h>
//#include <CGAL\mst_orient_normals.h>
//#include <CGAL\Advancing_front_surface_reconstruction.h>
//#include <vector>
//#include <fstream>
//// Types
//typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
//typedef Kernel::FT FT;
//typedef Kernel::Point_3 Point;
//typedef Kernel::Vector_3 Vector;
//typedef CGAL::Point_set_3<Point, Vector> Point_set;
//typedef std::pair<Point, Vector> Point_with_normal;
//typedef CGAL::First_of_pair_property_map<Point_with_normal> Point_map;
//typedef CGAL::Second_of_pair_property_map<Point_with_normal> Normal_map;
//typedef Kernel::Sphere_3 Sphere;
//typedef std::vector<Point_with_normal> PointList;
//typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
//typedef CGAL::Poisson_reconstruction_function<Kernel> Poisson_reconstruction_function;
//typedef CGAL::Surface_mesh_default_triangulation_3 STr;
//typedef CGAL::Surface_mesh_complex_2_in_triangulation_3<STr> C2t3;
//typedef CGAL::Implicit_surface_3<Kernel, Poisson_reconstruction_function> Surface_3;
//
//typedef CGAL::Surface_mesh<Kernel::Point_3>                 SurfMesh;
//
//typedef boost::graph_traits<SurfMesh>::vertex_descriptor           vertex_descriptor;
//typedef boost::graph_traits<SurfMesh>::face_descriptor           face_descriptor;
////typedef boost::property_map<SurfMesh, CGAL::vertex_point_t>::type  VPMap;
////typedef SurfMesh::template Property_map<vertex_descriptor, Vector> VNMap;
////typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
//
//std::shared_ptr<tnbLib::Entity3d_Triangulation> 
//tnbLib::Geo_Tools::PoissonSurfaceRecon_cgal(const Entity3d_Triangulation& theTris)
//{
//	static auto getPoint = [](const Point& thePt)
//	{
//		Pnt3d pt(thePt.x(), thePt.y(), thePt.z());
//		return std::move(pt);
//	};
//	SurfMesh surfMesh;
//	std::vector<Point> pts;
//	std::vector<SurfMesh::Vertex_index> ids;
//	for (const auto& p : theTris.Points())
//	{
//		auto [x, y, z] = p.Components();
//		Point p3(x, y, z);
//		pts.push_back(p3);
//		auto id = surfMesh.add_vertex(p3);
//		ids.push_back(id);
//	}
//	for (const auto& x : theTris.Connectivity())
//	{
//		auto v0 = x.Value(0);
//		auto v1 = x.Value(1);
//		auto v2 = x.Value(2);
//
//		surfMesh.add_face(ids.at(Index_Of(v0)), ids.at(Index_Of(v1)), ids.at(Index_Of(v2)));
//	}
//	CGAL::Polygon_mesh_processing::stitch_borders(surfMesh);
//
//	auto vnormals = surfMesh.add_property_map<vertex_descriptor, Vector>("v:normals", CGAL::NULL_VECTOR).first;
//	auto fnormals = surfMesh.add_property_map<face_descriptor, Vector>("f:normals", CGAL::NULL_VECTOR).first;
//
//	CGAL::Polygon_mesh_processing::compute_normals(surfMesh, vnormals, fnormals);
//	std::vector<Point_with_normal> pws;
//	pws.reserve(pts.size());
//	for (size_t i = 0; i < pts.size(); i++)
//	{
//		const auto& pt = pts.at(i);
//		const auto& id = ids.at(i);
//
//		const auto& normal = vnormals[id];
//		auto paired = std::make_pair(pt, normal);
//		pws.push_back(std::move(paired));
//	}
//
//	double average_spacing = CGAL::compute_average_spacing<CGAL::Sequential_tag>
//		(pws, 6, CGAL::parameters::point_map(CGAL::First_of_pair_property_map<Point_with_normal>()));
//	
//	// Simplify using a grid of size 2 * average spacing
//	{
//		Point_set point_set;
//		for (const auto& x : pts)
//		{
//			point_set.insert(x);
//		}
//
//		point_set.add_normal_map();
//		Point_set::iterator it = point_set.begin();
//		for (size_t i = 0; i < pts.size(); i++)
//		{
//			const auto& id = ids.at(i);
//			const auto& normal = vnormals[id];
//
//			point_set.normal(*(it++)) = normal;
//		}
//		/*typename Point_set::iterator gsim_it = CGAL::grid_simplify_point_set(point_set, 2. * average_spacing);
//		point_set.remove(gsim_it, point_set.end());
//		std::cout << point_set.number_of_removed_points()
//			<< " point(s) removed after simplification." << std::endl;*/
//
//		/*CGAL::jet_estimate_normals<CGAL::Sequential_tag>
//			(point_set, 24);*/ // Use 24 neighbors
//		// Orientation of normals, returns iterator to first unoriented point
//		//typename Point_set::iterator unoriented_points_begin =
//		//	CGAL::mst_orient_normals(point_set, 24); // Use 24 neighbors
//		//point_set.remove(unoriented_points_begin, point_set.end());
//
//		pws.clear();
//		pws.reserve(point_set.size());
//
//		for (size_t i = 0; i < point_set.size(); i++)
//		{
//			auto paired = std::make_pair(point_set.point(i), point_set.normal(i));
//			pws.push_back(std::move(paired));
//		}
//		typedef std::array<std::size_t, 3> Facet; // Triple of indices
//		std::vector<Facet> facets;
//		// The function is called using directly the points raw iterators
//		CGAL::advancing_front_surface_reconstruction(point_set.points().begin(),
//			point_set.points().end(),
//			std::back_inserter(facets));
//		std::cout << facets.size()
//			<< " facet(s) generated by reconstruction." << std::endl;
//
//		auto mesh = std::make_shared<Entity3d_Triangulation>();
//		auto& pts = mesh->Points();
//		for (const auto& x : point_set.points())
//		{
//			Pnt3d pt(x.x(), x.y(), x.z());
//			pts.push_back(std::move(pt));
//		}
//
//		auto& ids = mesh->Connectivity();
//		for (const auto& x : facets)
//		{
//			connectivity::triple t;
//			t.Value(0) = x.at(0) + 1;
//			t.Value(1) = x.at(1) + 1;
//			t.Value(2) = x.at(2) + 1;
//			ids.push_back(std::move(t));
//		}
//		return std::move(mesh);
//
//		SurfMesh poly;
//		if (CGAL::poisson_surface_reconstruction_delaunay
//		(pws.begin(), pws.end(),
//			CGAL::First_of_pair_property_map<Point_with_normal>(),
//			CGAL::Second_of_pair_property_map<Point_with_normal>(),
//			poly, average_spacing))
//		{
//			auto mesh = std::make_shared<Entity3d_Triangulation>();
//			auto& pts = mesh->Points();
//			std::map<Standard_Integer, Standard_Integer> vtx_indx;
//			Standard_Integer i = 0;
//			for (const auto& v : poly.vertices())
//			{
//				auto paired = std::make_pair(v, ++i);
//				vtx_indx.insert(std::move(paired));
//				const auto& x = poly.point(v);
//				Pnt3d pt(x.x(), x.y(), x.z());
//				pts.push_back(std::move(pt));
//			}
//
//			auto& ids = mesh->Connectivity();
//			std::vector<std::pair<Standard_Integer, Standard_Integer>> indx_index;
//			Standard_Integer indx = 0;
//			for (const auto& fi : poly.faces())
//			{
//				auto hf = poly.halfedge(fi);
//				connectivity::triple t;
//				Standard_Integer k = 0;
//				for (auto hi : halfedges_around_face(hf, poly))
//				{
//					auto vi = target(hi, poly);
//					Debug_Bad_Index(k, 0, 2);
//					t.Value(k++) = vtx_indx.at(vi);
//
//				}
//				ids.push_back(std::move(t));
//			}
//			return std::move(mesh);
//		}
//		else
//		{
//			std::cout << "Failed!" << std::endl;
//			return nullptr;
//		}
//	}
//
//	SurfMesh poly;
//	if (CGAL::poisson_surface_reconstruction_delaunay
//	(pws.begin(), pws.end(),
//		CGAL::First_of_pair_property_map<Point_with_normal>(),
//		CGAL::Second_of_pair_property_map<Point_with_normal>(),
//		poly, average_spacing))
//	{
//		PAUSE;
//		auto mesh = std::make_shared<Entity3d_Triangulation>();
//		auto& pts = mesh->Points();
//		std::map<Standard_Integer, Standard_Integer> vtx_indx;
//		Standard_Integer i = 0;
//		for (const auto& v : poly.vertices())
//		{
//			auto paired = std::make_pair(v, ++i);
//			vtx_indx.insert(std::move(paired));
//			const auto& x = poly.point(v);
//			Pnt3d pt(x.x(), x.y(), x.z());
//			pts.push_back(std::move(pt));
//		}
//
//		auto& ids = mesh->Connectivity();
//		std::vector<std::pair<Standard_Integer, Standard_Integer>> indx_index;
//		Standard_Integer indx = 0;
//		for (const auto& fi : poly.faces())
//		{
//			auto hf = poly.halfedge(fi);
//			connectivity::triple t;
//			Standard_Integer k = 0;
//			for (auto hi : halfedges_around_face(hf, poly))
//			{
//				auto vi = target(hi, poly);
//				Debug_Bad_Index(k, 0, 2);
//				t.Value(k++) = vtx_indx.at(vi);
//
//			}
//			ids.push_back(std::move(t));
//		}
//		return std::move(mesh);
//	}
//	else
//	{
//		std::cout << "Failed!" << std::endl;
//		return nullptr;
//	}
//}