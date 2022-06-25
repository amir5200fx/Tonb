#include <Geo3d_DelTri_CGAL.hxx>

#include <Entity3d_Tetrahedralization.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#ifdef Handle
#undef Handle
#endif // Handle

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Delaunay_triangulation_cell_base_3.h>
#include <CGAL/Triangulation_vertex_base_with_info_3.h>
#include <CGAL/spatial_sort.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef CGAL::Triangulation_vertex_base_with_info_3<unsigned, K>    Vb;
typedef CGAL::Delaunay_triangulation_cell_base_3<K>                 Cb;
typedef CGAL::Triangulation_data_structure_3<Vb, Cb>                Tds;
//Use the Fast_location tag. Default or Compact_location works too.
typedef CGAL::Delaunay_triangulation_3<K, Tds, CGAL::Fast_location> Delaunay;
typedef Delaunay::Point                                             Point;
typedef CGAL::Spatial_sort_traits_adapter_3<K, Point*> Search_traits;

#include <list>

namespace tnbLib
{

	template <class InputIterator>
	void insert_with_info(Delaunay& cdt, InputIterator first, InputIterator last)
	{
		std::vector<std::ptrdiff_t> indices;
		std::vector<Point> points;
		std::ptrdiff_t index = 0;

		for (InputIterator it = first; it != last; ++it) 
		{
			points.push_back(*it);
			indices.push_back(index++);
		}

		CGAL::spatial_sort(indices.begin(), indices.end(), Search_traits(&(points[0]), cdt.geom_traits()));

		Delaunay::Vertex_handle v_hint;
		Delaunay::Cell_handle hint;
		for (typename std::vector<std::ptrdiff_t>::const_iterator
			it = indices.begin(), end = indices.end();
			it != end; ++it) {
			v_hint = cdt.insert(points[*it], hint);
			if (v_hint != Delaunay::Vertex_handle()) {
				v_hint->info() = (unsigned)*it;
				hint = v_hint->cell();
			}
		}
	}
}

void tnbLib::cgalLib::Geo3d_DelTri::Perform()
{
	std::vector<Point> cgal_pnts;
	cgal_pnts.reserve(thePoints_.size());
	for (const auto& x : thePoints_)
	{
		Point pt(x.X(), x.Y(), x.Z());
		cgal_pnts.push_back(std::move(pt));
	}

	Delaunay dt(cgal_pnts.begin(), cgal_pnts.end());
	//Delaunay::size_type n = dt.number_of_vertices();

	insert_with_info(dt, dt.points_begin(), dt.points_end());

	theTriangulation_ = std::make_shared<Entity3d_Tetrahedralization>();
	Debug_Null_Pointer(theTriangulation_);

	auto& pnts = Triangulation()->Points();
	auto& indices = Triangulation()->Connectivity();

	pnts.resize(dt.number_of_vertices());
	Delaunay::Finite_vertices_iterator pIter;
	for (pIter = dt.finite_vertices_begin(); pIter != dt.finite_vertices_end(); pIter++)
	{
		const auto& pt = pIter->point();
		pnts[pIter->info()] = Pnt3d(pt.x(), pt.y(), pt.z());
	}

	indices.reserve(dt.number_of_cells());
	Delaunay::Finite_cells_iterator iter;
	for (iter = dt.finite_cells_begin(); iter != dt.finite_cells_end(); iter++)
	{
		connectivity::quadruple q;

		q.Value(0) = iter->vertex(0)->info() + 1;
		q.Value(1) = iter->vertex(1)->info() + 1;
		q.Value(2) = iter->vertex(2)->info() + 1;
		q.Value(3) = iter->vertex(3)->info() + 1;

		indices.push_back(std::move(q));
	}
	Change_IsDone() = Standard_True;
}