#include <Geo2d_DelTri_CGAL.hxx>

#include <Entity2d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_2.h>
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
typedef CGAL::Triangulation_face_base_2<K>           Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>              TDS;
typedef CGAL::Triangulation_2<K, TDS> DT;
typedef DT::Point   Point;
typedef CGAL::Spatial_sort_traits_adapter_2<K, Point*> Search_traits;

namespace tnbLib
{
	template <class InputIterator>
	void insert_with_info(DT& cdt, InputIterator first, InputIterator last)
	{
		std::vector<std::ptrdiff_t> indices;
		std::vector<Point> points;
		std::ptrdiff_t index = 0;

		for (InputIterator it = first; it != last; ++it) {
			points.push_back(*it);
			indices.push_back(index++);
		}

		CGAL::spatial_sort(indices.begin(), indices.end(), Search_traits(&(points[0]), cdt.geom_traits()));

		DT::Vertex_handle v_hint;
		DT::Face_handle hint;
		for (typename std::vector<std::ptrdiff_t>::const_iterator
			it = indices.begin(), end = indices.end();
			it != end; ++it) {
			v_hint = cdt.insert(points[*it], hint);
			if (v_hint != DT::Vertex_handle()) {
				v_hint->info() = (unsigned)*it;
				hint = v_hint->face();
			}
		}
	}
}

void tnbLib::cgalLib::Geo2d_DelTri::Perform()
{
	std::vector<Point> cgal_pnts;
	for (const auto& p : thePoints_)
	{
		cgal_pnts.push_back(Point(p.X(), p.Y()));
	}
	DT dt;
	dt.insert(cgal_pnts.begin(), cgal_pnts.end());

	insert_with_info(dt, dt.points_begin(), dt.points_end());

	theTriangulation_ = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(theTriangulation_);

	auto& pnts = Triangulation()->Points();
	auto indices = Triangulation()->Connectivity();

	pnts.resize(dt.number_of_vertices());
	DT::Finite_vertices_iterator pIter;
	for (pIter = dt.finite_vertices_begin(); pIter != dt.finite_vertices_end(); pIter++)
	{
		const auto& pt = pIter->point();
		pnts[pIter->info()] = Pnt2d(pt.x(), pt.y());
	}

	indices.reserve(dt.number_of_faces());
	DT::Finite_faces_iterator iter;
	for (iter = dt.finite_faces_begin(); iter != dt.finite_faces_end(); iter++)
	{
		connectivity::triple t;

		DT::Triangle trr = dt.triangle(iter);


		t.Value(0) = iter->vertex(0)->info() + 1;
		t.Value(1) = iter->vertex(1)->info() + 1;
		t.Value(2) = iter->vertex(2)->info() + 1;

		indices.push_back(t);
	}

	Change_IsDone() = Standard_True;
}