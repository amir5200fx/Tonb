#pragma once
#ifndef _Geo_CmptLib_Header
#define _Geo_CmptLib_Header

#include <Pnt2d.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_TriangleFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Geo_Module.hxx>

#include <vector>

namespace tnbLib
{

	class Geo_CmptLib
	{

	public:

		static TnbGeo_EXPORT Standard_Real 
			Area
			(
				const Entity2d_Box& b
			);

		static TnbGeo_EXPORT Standard_Real 
			IxBar
			(
				const Entity2d_Box& b
			);

		static TnbGeo_EXPORT Standard_Real 
			IyBar
			(
				const Entity2d_Box& b
			);

		static TnbGeo_EXPORT Standard_Real 
			Ix
			(
				const Entity2d_Box& b, 
				const Standard_Real y0
			);

		static TnbGeo_EXPORT Standard_Real 
			Iy
			(
				const Entity2d_Box& b,
				const Standard_Real x0
			);

		static TnbGeo_EXPORT Standard_Real 
			Mx
			(
				const Entity2d_Box& b,
				const Standard_Real y0
			);

		static TnbGeo_EXPORT Standard_Real 
			My
			(
				const Entity2d_Box& b,
				const Standard_Real x0
			);

		static TnbGeo_EXPORT Standard_Real
			Area
			(
				const Entity2d_Polygon& thePoly
			);

		static TnbGeo_EXPORT Standard_Real
			Area
			(
				const Entity2d_Triangle& t
			);

		static TnbGeo_EXPORT Standard_Real
			CxProductArea
			(
				const Entity2d_Polygon& thePoly
			);

		static TnbGeo_EXPORT Standard_Real
			CxProductArea
			(
				const Entity2d_Triangle& t
			);

		static TnbGeo_EXPORT Standard_Real
			CyProductArea
			(
				const Entity2d_Polygon& thePoly
			);

		static TnbGeo_EXPORT Standard_Real 
			CyProductArea
			(
				const Entity2d_Triangle& t
			);

		static TnbGeo_EXPORT Pnt2d
			Centre
			(
				const Entity2d_Polygon& thePoly
			);

		static TnbGeo_EXPORT Pnt2d 
			Centre
			(
				const Entity2d_Triangle& t
			);

		static TnbGeo_EXPORT Standard_Real
			Ix
			(
				const Entity2d_Polygon& thePoly,
				const Standard_Real y0
			);

		static TnbGeo_EXPORT Standard_Real 
			Ix
			(
				const Entity2d_Triangle& t,
				const Standard_Real y0
			);

		static TnbGeo_EXPORT Standard_Real
			Iy
			(
				const Entity2d_Polygon& thePoly,
				const Standard_Real x0
			);

		static TnbGeo_EXPORT Standard_Real 
			Iy
			(
				const Entity2d_Triangle& t,
				const Standard_Real x0
			);

		static TnbGeo_EXPORT Standard_Real
			Ixy
			(
				const Entity2d_Polygon& thePoly,
				const Pnt2d& theC
			);

		static TnbGeo_EXPORT Standard_Real
			Ixi
			(
				const Standard_Real IxiBar, 
				const Standard_Real theArea, 
				const Standard_Real dxi
			);

		static TnbGeo_EXPORT Standard_Real
			Gyradius
			(
				const Standard_Real Ix,
				const Standard_Real theArea
			);

		static TnbGeo_EXPORT Standard_Real
			Ixi
			(
				const std::vector<Standard_Real>& ix,
				const std::vector<Standard_Real>& Ax,
				const std::vector<Standard_Real>& dx
			);

		static TnbGeo_EXPORT Standard_Real
			Ixy
			(
				const Standard_Real IxyBar,
				const Standard_Real dx,
				const Standard_Real dy, 
				const Standard_Real Area
			);

		static Standard_Real Mx(const Entity2d_Triangulation& t, const Standard_Real y0);

		static Standard_Real My(const Entity2d_Triangulation& t, const Standard_Real x0);

		static Pnt2d Centre(const Entity2d_Triangulation& t);


	};
}

#endif // !_Geo_CmptLib_Header
