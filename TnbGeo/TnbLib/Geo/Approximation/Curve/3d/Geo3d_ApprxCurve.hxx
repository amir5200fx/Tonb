#pragma once
#ifndef _Geo3d_ApprxCurve_Header
#define _Geo3d_ApprxCurve_Header

#include <Geo2d_ApprxCurve.hxx>
#include <Entity3d_Chain.hxx>
#include <Global_Handle.hxx>

#include <opencascade/Geom_Curve.hxx>

#include <memory>

namespace tnbLib
{

	typedef Geo_ApprxCurve<Handle(Geom_Curve), true>
		Geo3d_ApprxCurve;
}

#endif // !_Geo3d_ApprxCurve_Header