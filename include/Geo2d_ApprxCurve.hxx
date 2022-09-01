#pragma once
#ifndef _Geo2d_ApprxCurve_Header
#define _Geo2d_ApprxCurve_Header

#include <Standard_Handle.hxx>
#include <Geo_ApprxCurve.hxx>
#include <Entity2d_Chain.hxx>

#include <Geom2d_Curve.hxx>

#include <memory>

namespace tnbLib
{

	typedef Geo_ApprxCurve<Handle(Geom2d_Curve), true>
		Geo2d_ApprxCurve;
}

#endif // !_Geo2d_ApprxCurve_Header