#pragma once
#ifndef _Geo_SizeFunctionTraits_Header
#define _Geo_SizeFunctionTraits_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo3d_SizeFunctionFwd.hxx>
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	// Forward Declarations [3/1/2022 Amir]

	template<class T> struct point_type_from_sizeMap {};

	template<> struct point_type_from_sizeMap<Geo2d_SizeFunction> { typedef Pnt2d ptType; };
	template<> struct point_type_from_sizeMap<Geo3d_SizeFunction> { typedef Pnt3d ptType; };
}

#endif // !_Geo_SizeFunctionTraits_Header
