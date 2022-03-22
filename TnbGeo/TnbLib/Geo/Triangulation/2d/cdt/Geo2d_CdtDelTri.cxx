#include <Geo2d_CdtDelTri.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>
#include <Entity_StaticData.hxx>
#ifdef Handle
#undef Handle
#endif // Handle
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_conformer_2.h>
#include <CGAL/Polygon_2.h>

struct FaceInfo2
{
	FaceInfo2() {}
	int nesting_level;
	bool in_domain() {
		return nesting_level % 2 == 1;
	}
};

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_with_info_2<unsigned, K> Vb;
typedef CGAL::Constrained_triangulation_face_base_2<K>           Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>              TDS;
typedef CGAL::Exact_predicates_tag                               Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag> CDT;
typedef CDT::Point          Point;
typedef CGAL::Spatial_sort_traits_adapter_2<K, Point*> Search_traits;

template <class InputIterator>
void insert_with_info(CDT& cdt, InputIterator first, InputIterator last)
{
	std::vector<std::ptrdiff_t> indices;
	std::vector<Point> points;
	std::ptrdiff_t index = 0;

	for (InputIterator it = first; it != last; ++it) {
		points.push_back(*it);
		indices.push_back(index++);
	}

	CGAL::spatial_sort(indices.begin(), indices.end(), Search_traits(&(points[0]), cdt.geom_traits()));

	CDT::Vertex_handle v_hint;
	CDT::Face_handle hint;
	for (typename std::vector<std::ptrdiff_t>::const_iterator
		it = indices.begin(), end = indices.end();
		it != end; ++it) {
		v_hint = cdt.insert(points[*it], hint);
		if (v_hint != CDT::Vertex_handle()) {
			v_hint->info() = (unsigned)*it;
			hint = v_hint->face();
		}
	}
}

typedef CGAL::Polygon_2<K> Polygon_2;

void tnbLib::Geo2d_CdtDelTri::Perform()
{
	CDT cdt;
	//std::vector<Point> Vertices;

	for (const auto& x : theConstraints_)
	{
		Debug_Null_Pointer(x);
		Polygon_2 polygon;

		for (const auto& pt : x->Points())
		{
			polygon.push_back(Point(pt.X(), pt.Y()));
		}

		cdt.insert_constraint(polygon.vertices_begin(), polygon.vertices_end(), false);
	}

	Standard_Integer K = 0;
	for (const auto& x : thePts_)
	{
		cdt.insert(Point(x.X(), x.Y()));
	}

	CGAL::make_conforming_Delaunay_2(cdt);

	insert_with_info(cdt, cdt.points_begin(), cdt.points_end());

	theData_ = std::make_shared<staticData>();
	Debug_Null_Pointer(Data());

	auto& Pts = Data()->Points();
	auto& Indices = Data()->Connectivity();

	Pts.resize(cdt.number_of_vertices());
	CDT::Finite_vertices_iterator pIter;
	for (pIter = cdt.finite_vertices_begin(); pIter != cdt.finite_vertices_end(); pIter++)
	{
		const auto& pt = pIter->point();
		Pts[pIter->info()] = Pnt2d(pt.x(), pt.y());
	}

	Indices.reserve(cdt.number_of_faces());
	CDT::Finite_faces_iterator iter;
	for (iter = cdt.finite_faces_begin(); iter != cdt.finite_faces_end(); iter++)
	{
		connectivity::triple t;

		CDT::Triangle trr = cdt.triangle(iter);


		t.Value(0) = iter->vertex(0)->info() + 1;
		t.Value(1) = iter->vertex(1)->info() + 1;
		t.Value(2) = iter->vertex(2)->info() + 1;

		if (HandleDegeneracy_ AND trr.area() < 1e-12) continue;

		Indices.push_back(t);
	}

	Change_IsDone() = Standard_True;
}