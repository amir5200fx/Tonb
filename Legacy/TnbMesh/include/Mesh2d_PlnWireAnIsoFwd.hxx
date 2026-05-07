#pragma once
#ifndef _Mesh2d_PlnWireAnIsoFwd_Header
#define _Mesh2d_PlnWireAnIsoFwd_Header

#include <Mesh2d_PlnCurveAnIsoFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/19/2021 Amir]
	template<class MeshPlnCurve>
	class Mesh_PlnWire;

	typedef Mesh_PlnWire<Mesh2d_PlnCurveAnIso> Mesh2d_PlnWireAnIso;
}

#endif // !_Mesh2d_PlnWireAnIsoFwd_Header
