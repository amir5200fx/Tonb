#pragma once
#ifndef _Mesh2d_VolumetricSizeMapControlFwd_Header
#define _Mesh2d_VolumetricSizeMapControlFwd_Header

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;

	template<class GeomType> class Mesh_VolumetricSizeMapControl;

	typedef Mesh_VolumetricSizeMapControl<Cad2d_Plane> Mesh2d_VolumetricSizeMapControl;
}

#endif // !_Mesh2d_VolumetricSizeMapControlFwd_Header
