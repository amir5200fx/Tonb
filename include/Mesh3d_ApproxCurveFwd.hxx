#pragma once
#ifndef _Mesh3d_ApproxCurveFwd_Header
#define _Mesh3d_ApproxCurveFwd_Header

#include <Standard_Handle.hxx>

class Geom_Curve;

namespace tnbLib
{

	// Forward Declarations [11/4/2022 Amir]

	template<class CurveType>
	class Mesh_ApproxCurve;

	typedef Mesh_ApproxCurve<Handle(Geom_Curve)> Mesh3d_ApproxCurve;
}

#endif // !_Mesh3d_ApproxCurveFwd_Header
