#include <Geo2d_PolygonDelTri.hxx>

#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef Handle
#undef Handle
#endif // Handle
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_conformer_2.h>
#include <CGAL/Polygon_2.h>
#include <iostream>

struct FaceInfo2
{
	FaceInfo2() {}
	int nesting_level;
	bool in_domain() {
		return nesting_level % 2 == 1;
	}
};

typedef CGAL::Exact_predicates_inexact_constructions_kernel       K;

typedef CGAL::Triangulation_vertex_base_with_info_2<unsigned, K>    Vb;
typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo2, K>    Fbb;
typedef CGAL::Constrained_triangulation_face_base_2<K, Fbb>        Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>               TDS;
typedef CGAL::Exact_predicates_tag                                Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>  CDT;
typedef CDT::Point                                                Point;
typedef CGAL::Polygon_2<K>                                        Polygon_2;
typedef CDT::Face_handle                                          Face_handle;
typedef CGAL::Spatial_sort_traits_adapter_2<K, Point*>			Search_traits;

namespace tnbLib
{

	namespace cgalLib
	{

		

		void mark_domains(CDT& ct,
			Face_handle start,
			int index,
			std::list<CDT::Edge>& border)
		{
			if (start->info().nesting_level != -1) {
				return;
			}
			std::list<Face_handle> queue;
			queue.push_back(start);
			while (!queue.empty()) {
				Face_handle fh = queue.front();
				queue.pop_front();
				if (fh->info().nesting_level == -1) {
					fh->info().nesting_level = index;
					for (int i = 0; i < 3; i++) {
						CDT::Edge e(fh, i);
						Face_handle n = fh->neighbor(i);
						if (n->info().nesting_level == -1) {
							if (ct.is_constrained(e)) border.push_back(e);
							else queue.push_back(n);
						}
					}
				}
			}
		}

		//explore set of facets connected with non constrained edges,
		//and attribute to each such set a nesting level.
		//We start from facets incident to the infinite vertex, with a nesting
		//level of 0. Then we recursively consider the non-explored facets incident
		//to constrained edges bounding the former set and increase the nesting level by 1.
		//Facets in the domain are those with an odd nesting level.

		void mark_domains(CDT& cdt)
		{
			for (CDT::Face_handle f : cdt.all_face_handles()) {
				f->info().nesting_level = -1;
			}
			std::list<CDT::Edge> border;
			mark_domains(cdt, cdt.infinite_face(), 0, border);
			while (!border.empty()) {
				CDT::Edge e = border.front();
				border.pop_front();
				Face_handle n = e.first->neighbor(e.second);
				if (n->info().nesting_level == -1) {
					mark_domains(cdt, n, e.first->info().nesting_level + 1, border);
				}
			}
		}

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
	}
}

void tnbLib::Geo2d_PolygonDelTri::Perform()
{
	if (thePolygons_.empty())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no polygon has been found." << endl
			<< abort(FatalError);
	}

	//Insert the polygons into a constrained triangulation
	CDT cdt;
	for (const auto& x : thePolygons_)
	{
		Polygon_2 poly;
		for (const auto& p : x->Points())
		{
			poly.push_back({ p.X(), p.Y() });
		}
		cdt.insert_constraint(poly.vertices_begin(), poly.vertices_end(), true);
	}

	CGAL::make_conforming_Delaunay_2(cdt);

	//Mark facets that are inside the domain bounded by the polygon
	cgalLib::mark_domains(cdt);

	cgalLib::insert_with_info(cdt, cdt.points_begin(), cdt.points_end());

	auto tri = std::make_shared<Entity2d_Triangulation>();
	auto& pts = tri->Points();
	auto& indices = tri->Connectivity();

	pts.resize(cdt.number_of_vertices());
	CDT::Finite_vertices_iterator pIter;
	for (pIter = cdt.finite_vertices_begin(); pIter != cdt.finite_vertices_end(); pIter++)
	{
		const auto& pt = pIter->point();
		pts.at(pIter->info()) = Pnt2d(pt.x(), pt.y());
	}

	indices.reserve(cdt.number_of_faces());
	CDT::Finite_faces_iterator iter;
	for (iter = cdt.finite_faces_begin(); iter != cdt.finite_faces_end(); iter++)
	{
		connectivity::triple t;

		CDT::Triangle trr = cdt.triangle(iter);

		if (NOT iter->info().in_domain()) continue;

		t.Value(0) = iter->vertex(0)->info() + 1;
		t.Value(1) = iter->vertex(1)->info() + 1;
		t.Value(2) = iter->vertex(2)->info() + 1;

		indices.push_back(std::move(t));
	}
	theTriangulation_ = std::move(tri);
	Change_IsDone() = Standard_True;
}