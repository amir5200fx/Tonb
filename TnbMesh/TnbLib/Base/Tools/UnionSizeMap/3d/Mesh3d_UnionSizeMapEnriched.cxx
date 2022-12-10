#include <Mesh3d_UnionSizeMap.hxx>

#include <Geo3d_DelTri_Fade3d.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Geo_Tools.hxx>

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

namespace tnbLib
{

	template <class InputIterator>
	void IndexPnts(Delaunay& cdt, InputIterator first, InputIterator last)
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

	auto GetTets(const Delaunay& dt)
	{
		auto tet = std::make_shared<Entity3d_Tetrahedralization>();
		Debug_Null_Pointer(tet);

		auto& pnts = tet->Points();
		auto& indices = tet->Connectivity();

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
		return std::move(tet);
	}

	auto ApplyEnrich(const Standard_Real h0, const Standard_Real h1, const Standard_Real h2, const Standard_Real h3, const Standard_Real tol)
	{
		auto a0 = std::abs(h0 - tol);
		auto a1 = std::abs(h1 - tol);
		auto a2 = std::abs(h2 - tol);
		auto a3 = std::abs(h3 - tol);

		return a0 AND a1 AND a2 AND a3;
	}

	auto ApplyEnrich(const Standard_Real h0, const Standard_Real h1, const Standard_Real h2, const Standard_Real tol)
	{
		auto a0 = std::abs(h0 - tol);
		auto a1 = std::abs(h1 - tol);
		auto a2 = std::abs(h2 - tol);

		return a0 AND a1 AND a2;
	}
}

std::shared_ptr<tnbLib::Entity3d_Tetrahedralization> 
tnbLib::Mesh3d_UnionSizeMap::EnrichedTetrahedralization
(
	const std::vector<Pnt3d>& thePnts,
	const Standard_Real theTol
) const
{
	fadeLib::Geo3d_DelTri delTri(thePnts);
	delTri.Perform();

	auto tets = delTri.Triangulation();
	return tets;
	/*std::vector<Point> cgal_pnts;
	cgal_pnts.reserve(thePnts.size());
	for (const auto& x : thePnts)
	{
		Point pt(x.X(), x.Y(), x.Z());
		cgal_pnts.push_back(std::move(pt));
	}

	Delaunay dt(cgal_pnts.begin(), cgal_pnts.end());

	IndexPnts(dt, dt.points_begin(), dt.points_end());

	auto tets = GetTets(dt);*/
	const auto& pts = tets->Points();
	const auto& indices = tets->Connectivity();

	auto epts = tets->Points();
	for (const auto& i : indices)
	{
		auto v0 = i.Value(0);
		auto v1 = i.Value(1);
		auto v2 = i.Value(2);
		auto v3 = i.Value(3);

		const auto& p0 = pts.at(Index_Of(v0));
		const auto& p1 = pts.at(Index_Of(v1));
		const auto& p2 = pts.at(Index_Of(v2));
		const auto& p3 = pts.at(Index_Of(v3));

		auto h0 = ElementSize(p0);
		auto h1 = ElementSize(p1);
		auto h2 = ElementSize(p2);
		auto h3 = ElementSize(p3);

		if (ApplyEnrich(h0, h1, h2, h3, theTol))
		{
			epts.push_back(Geo_Tools::CalcCentre(p0, p1, p2, p3));
		}

		if (ApplyEnrich(h0, h1, h2, theTol))
		{
			epts.push_back(Geo_Tools::CalcCentre(p0, p1, p2));
		}

		if (ApplyEnrich(h0, h1, h3, theTol))
		{
			epts.push_back(Geo_Tools::CalcCentre(p0, p1, p3));
		}

		if (ApplyEnrich(h1, h3, h2, theTol))
		{
			epts.push_back(Geo_Tools::CalcCentre(p1, p3, p2));
		}

		if (ApplyEnrich(h0, h3, h2, theTol))
		{
			epts.push_back(Geo_Tools::CalcCentre(p0, p3, p2));
		}
	}
	fadeLib::Geo3d_DelTri newDelTri(epts);
	newDelTri.Perform();
	return newDelTri.Triangulation();
	/*std::cout << "importing the vertices..." << std::endl;
	auto vtx = dt.vertices_begin();
	for (const auto& x : epts)
	{
		Point pt(x.X(), x.Y(), x.Z());
		vtx = dt.insert(pt, vtx);
	}
	std::cout << "the vertices have been imported!" << std::endl;

	IndexPnts(dt, dt.points_begin(), dt.points_end());

	auto newTets = GetTets(dt);
	std::cout << "tets are gotten!" << std::endl;
	return std::move(newTets);*/
}