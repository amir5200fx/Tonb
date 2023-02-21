#include <GeoSlicer2d_PolyLine.hxx>

#include <GeoExtrude_Polyline.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_AdTree.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>

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

namespace tnbLib
{

	auto GetTris3d(const Entity2d_Triangulation& theTris)
	{
		std::vector<Pnt3d> pnts;
		pnts.reserve(theTris.NbPoints());
		for (const auto& x : theTris.Points())
		{
			auto p3 = Pnt3d(x.X(), x.Y(), 0);
			pnts.push_back(std::move(p3));
		}
		auto ids = theTris.Connectivity();
		auto tri = std::make_shared<Entity3d_Triangulation>(std::move(pnts), std::move(ids));
		return std::move(tri);
	}
}

namespace tnbLib
{

	namespace slicerLib
	{

		struct Triangle
		{
			connectivity::triple v;		
		};

		struct Node
		{
			typedef Pnt2d ptType;
			Pnt2d pt;
			std::shared_ptr<Triangle> tri;
		};
	}
}

namespace tnbLib
{

	auto RetrieveTriangulation(const std::vector<std::shared_ptr<slicerLib::Node>>& theNodes, const std::vector<Pnt2d>& thePnts)
	{
		std::map<Standard_Integer, Pnt2d> ptMap;
		for (const auto& x : theNodes)
		{
			const auto& t = x->tri->v;
			const auto& pt0 = thePnts.at(t.Value(0) - 1);
			{
				auto insert = ptMap.insert(std::make_pair(t.Value(0) - 1, pt0));
				if (NOT insert.second)
				{

				}
			}
			const auto& pt1 = thePnts.at(t.Value(1) - 1);
			{
				auto insert = ptMap.insert(std::make_pair(t.Value(1) - 1, pt1));
				if (NOT insert.second)
				{

				}
			}
			const auto& pt2 = thePnts.at(t.Value(2) - 1);
			{
				auto insert = ptMap.insert(std::make_pair(t.Value(2) - 1, pt2));
				if (NOT insert.second)
				{

				}
			}
		}
		std::vector<Pnt2d> pnts;
		pnts.reserve(ptMap.size());
		for (const auto& x : ptMap)
		{
			pnts.push_back(x.second);
		}
		std::map<Standard_Integer, Standard_Integer> idxMap;
		Standard_Integer k = 0;
		for (const auto& x : ptMap)
		{
			auto iter = idxMap.find(x.first);
			if (iter IS_EQUAL idxMap.end())
			{
				auto paired = std::make_pair(x.first, ++k);
				idxMap.insert(std::move(paired));
			}
		}
		std::vector<connectivity::triple> ids;
		ids.reserve(theNodes.size());
		for (const auto& node : theNodes)
		{
			const auto& x = node->tri->v;
			auto v0 = x.Value(0) - 1;
			auto v1 = x.Value(1) - 1;
			auto v2 = x.Value(2) - 1;
			connectivity::triple t;
			t.Value(0) = idxMap.at(v0);
			t.Value(1) = idxMap.at(v1);
			t.Value(2) = idxMap.at(v2);
			ids.push_back(std::move(t));
		}
		auto t = std::make_shared<Entity2d_Triangulation>(std::move(pnts), std::move(ids));
		return std::move(t);
	}
}

void tnbLib::GeoSlicer2d_PolyLine::Perform()
{
	if (NOT Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT Polyline())
	{
		FatalErrorIn(FunctionSIG)
			<< "no polyline has been loaded." << endl
			<< abort(FatalError);
	}
	static auto getPoint = [](const Point_3& thePt)
	{
		Pnt3d pt(thePt.x(), thePt.y(), thePt.z());
		return std::move(pt);
	};
	auto bbx = Geo_BoxTools::GetBox(Polyline()->Points(), 0);
	auto d = bbx.Diameter() * 0.1;
	auto extruder = std::make_shared<GeoExtrude_Polyline>();
	extruder->SetPolyline(Polyline());
	extruder->SetZ0(-d);
	extruder->SetZ1(+d);
	extruder->Perform();
	Debug_If_Condition_Message(NOT extruder->IsDone(), "the application is not performed.");

	auto tris3 = GetTris3d(*Mesh());
	
	//{// test [2/19/2023 Payvand]
	//	OFstream myFile("extruder.plt");
	//	extruder->Mesh()->ExportToPlt(myFile);
	//	tris3->ExportToPlt(myFile);
	//	std::exit(1);
	//}

	std::shared_ptr<Entity2d_Triangulation> sliced;
	{
		SurfMesh surfMesh;
		{
			std::vector<SurfMesh::Vertex_index> ids;
			for (const auto& p : tris3->Points())
			{
				auto [x, y, z] = p.Components();
				auto id = surfMesh.add_vertex(Point_3(x, y, z));
				ids.push_back(id);
			}
			for (const auto& x : tris3->Connectivity())
			{
				auto v0 = x.Value(0);
				auto v1 = x.Value(1);
				auto v2 = x.Value(2);

				surfMesh.add_face(ids.at(Index_Of(v0)), ids.at(Index_Of(v1)), ids.at(Index_Of(v2)));
			}
		}
		CGAL::Polygon_mesh_processing::stitch_borders(surfMesh);

		const auto& extruderTris = extruder->Mesh();

		SurfMesh clipper;
		{
			std::vector<SurfMesh::Vertex_index> ids;
			for (const auto& p : extruderTris->Points())
			{
				auto [x, y, z] = p.Components();
				auto id = clipper.add_vertex(Point_3(x, y, z));
				ids.push_back(id);
			}
			for (const auto& x : extruderTris->Connectivity())
			{
				auto v0 = x.Value(0);
				auto v1 = x.Value(1);
				auto v2 = x.Value(2);

				clipper.add_face(ids.at(Index_Of(v0)), ids.at(Index_Of(v1)), ids.at(Index_Of(v2)));
			}
		}
		CGAL::Polygon_mesh_processing::stitch_borders(clipper);

		if (CGAL::Polygon_mesh_processing::clip(surfMesh, clipper))
		{
			auto mesh = std::make_shared<Entity2d_Triangulation>();
			auto& pts = mesh->Points();
			std::map<Standard_Integer, Standard_Integer> vtx_indx;
			Standard_Integer i = 0;
			for (const auto& v : surfMesh.vertices())
			{
				auto paired = std::make_pair(v, ++i);
				vtx_indx.insert(std::move(paired));
				const auto& x = surfMesh.point(v);
				Pnt2d pt(x.x(), x.y());
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
			sliced = std::move(mesh);
		}
	}
	theClipped_ = std::move(sliced);
	Change_IsDone() = Standard_True;
	return;
	/*{
		OFstream myFile("sliced.plt");
		sliced->ExportToPlt(myFile);
		std::exit(1);
	}*/
	std::shared_ptr<Entity2d_Triangulation> inner;
	{
		SurfMesh surfMesh;
		{
			std::vector<SurfMesh::Vertex_index> ids;
			for (const auto& p : tris3->Points())
			{
				auto [x, y, z] = p.Components();
				auto id = surfMesh.add_vertex(Point_3(x, y, z));
				ids.push_back(id);
			}
			for (const auto& x : tris3->Connectivity())
			{
				auto v0 = x.Value(0);
				auto v1 = x.Value(1);
				auto v2 = x.Value(2);

				surfMesh.add_face(ids.at(Index_Of(v0)), ids.at(Index_Of(v1)), ids.at(Index_Of(v2)));
			}
		}
		CGAL::Polygon_mesh_processing::stitch_borders(surfMesh);

		const auto& extruderTris = extruder->Mesh();

		SurfMesh clipper;
		{
			std::vector<SurfMesh::Vertex_index> ids;
			for (const auto& p : extruderTris->Points())
			{
				auto [x, y, z] = p.Components();
				auto id = clipper.add_vertex(Point_3(x, y, z));
				ids.push_back(id);
			}
			for (const auto& x : extruderTris->Connectivity())
			{
				auto v0 = x.Value(0);
				auto v1 = x.Value(1);
				auto v2 = x.Value(2);

				clipper.add_face(ids.at(Index_Of(v0)), ids.at(Index_Of(v1)), ids.at(Index_Of(v2)));
			}
		}
		CGAL::Polygon_mesh_processing::stitch_borders(clipper);

		if (CGAL::Polygon_mesh_processing::clip(surfMesh, clipper))
		{
			auto mesh = std::make_shared<Entity2d_Triangulation>();
			auto& pts = mesh->Points();
			std::map<Standard_Integer, Standard_Integer> vtx_indx;
			Standard_Integer i = 0;
			for (const auto& v : surfMesh.vertices())
			{
				auto paired = std::make_pair(v, ++i);
				vtx_indx.insert(std::move(paired));
				const auto& x = surfMesh.point(v);
				Pnt2d pt(x.x(), x.y());
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
			inner = std::move(mesh);
		}
	}


	/*OFstream myFile("two.plt");
	sliced->ExportToPlt(myFile);
	inner->ExportToPlt(myFile);*/
	std::vector<std::shared_ptr<slicerLib::Node>> resTris;
	{
		auto bbx = Geo_BoxTools::GetBox(sliced->Points(), 0);
		bbx.Expand(bbx.Diameter() * 0.01);
		Geo_AdTree<std::shared_ptr<slicerLib::Node>> tree;
		{
			tree.SetGeometryRegion(bbx);
			tree.SetGeometryCoordFunc([](const std::shared_ptr<slicerLib::Node>& n)-> const auto& {return n->pt; });
			const auto& pnts = sliced->Points();
			for (const auto& x : sliced->Connectivity())
			{
				const auto& p0 = pnts.at(x.Value(0) - 1);
				const auto& p1 = pnts.at(x.Value(1) - 1);
				const auto& p2 = pnts.at(x.Value(2) - 1);

				auto pm = (p0 + p1 + p2) / 3.0;
				slicerLib::Triangle tRef = { x };
				slicerLib::Node nodeRef = { std::move(pm),std::make_shared<slicerLib::Triangle>(std::move(tRef)) };
				auto node = std::make_shared<slicerLib::Node>(std::move(nodeRef));

				tree.InsertToGeometry(node);
			}
		}
		const auto& pnts = inner->Points();
		for (const auto& x : inner->Connectivity())
		{
			const auto& p0 = pnts.at(x.Value(0) - 1);
			const auto& p1 = pnts.at(x.Value(1) - 1);
			const auto& p2 = pnts.at(x.Value(2) - 1);

			auto pm = (p0 + p1 + p2) / 3.0;
			auto b = Entity2d_Box::Box(pm, 1.0E-4);
			
			std::vector<std::shared_ptr<slicerLib::Node>> items;
			tree.GeometrySearch(b, items);
			for (const auto& i : items)
			{
				if (pm.Distance(i->pt) <= 1.0E-16)
				{
					tree.RemoveFromGeometry(i);
					break;
				}
			}
		}
		tree.RetrieveFromGeometryTo(resTris);
	}
	theClipped_ = RetrieveTriangulation(resTris, sliced->Points());
	
	Change_IsDone() = Standard_True;
}