#pragma once
#ifndef _Mesh2d_SizeMapControlFwd_Header
#define _Mesh2d_SizeMapControlFwd_Header

namespace tnbLib
{

	//- Forward Declarations
	class Cad2d_Plane;

	template<class GeomType> class Mesh_SizeMapControl;

	typedef Mesh_SizeMapControl<Cad2d_Plane> Mesh2d_SizeMapControl;
}

#endif // !_Mesh2d_SizeMapControlFwd_Header
