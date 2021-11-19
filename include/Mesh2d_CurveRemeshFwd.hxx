#pragma once
#ifndef _Mesh2d_CurveRemeshFwd_Header
#define _Mesh2d_CurveRemeshFwd_Header

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	template<class CurveType>
	class Mesh_CurveRemesh;

	typedef Mesh_CurveRemesh<Pln_Curve> Mesh2d_CurveRemesh;
}

#endif // !_Mesh2d_CurveRemeshFwd_Header
