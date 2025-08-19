#pragma once
#ifndef _Mesh2d_ApproxCurveFwd_Header
#define _Mesh2d_ApproxCurveFwd_Header

#include <Global_Handle.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [11/4/2022 Amir]

	template<class CurveType>
	class Mesh_ApproxCurve;

	typedef Mesh_ApproxCurve<Handle(Geom2d_Curve)> Mesh2d_ApproxCurve;
}

#endif // !_Mesh2d_ApproxCurveFwd_Header
