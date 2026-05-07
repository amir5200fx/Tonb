#pragma once
#ifndef _Geo2d_CGALCache_Header
#define _Geo2d_CGALCache_Header

#include <Entity2d_PolygonFwd.hxx>
#include <Geo_Module.hxx>

#ifdef Handle
#undef Handle
#endif // Handle

#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\Boolean_set_operations_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_2                                   Point_2;
typedef CGAL::Polygon_2<Kernel>                           Polygon_2;

namespace tnbLib
{

	class Geo2d_CGALCache
	{

		/*Private Data*/

		Polygon_2 thePolygon_;

	public:

		// default constructor [7/18/2023 Payvand]


		// constructors [7/18/2023 Payvand]

		TnbGeo_EXPORT Geo2d_CGALCache(const Entity2d_Polygon&);


		// Public functions and operators [7/18/2023 Payvand]

		const auto& Polygon() const { return thePolygon_; }

	};
}

#endif // !_Geo2d_CGALCache_Header
