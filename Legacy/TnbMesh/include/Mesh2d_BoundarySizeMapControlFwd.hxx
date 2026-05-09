#pragma once
#ifndef _Mesh2d_BoundarySizeMapControlFwd_Header
#define _Mesh2d_BoundarySizeMapControlFwd_Header

namespace tnbLib
{

	//- Forward Declarations
	class Cad2d_Plane;

	template<class GeomType> class Mesh_BoundarySizeMapControl;

	typedef Mesh_BoundarySizeMapControl<Cad2d_Plane> Mesh2d_BoundarySizeMapControl;
}

#endif // !_Mesh2d_BoundarySizeMapControlFwd_Header
