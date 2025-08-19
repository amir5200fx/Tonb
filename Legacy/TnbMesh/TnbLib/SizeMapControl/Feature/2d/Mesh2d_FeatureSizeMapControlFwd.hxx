#pragma once
#ifndef _Mesh2d_FeatureSizeMapControlFwd_Header
#define _Mesh2d_FeatureSizeMapControlFwd_Header

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;

	template<class GeomType> class Mesh_FeatureSizeMapControl;

	typedef Mesh_FeatureSizeMapControl<Cad2d_Plane> Mesh2d_FeatureSizeMapControl;
}

#endif // !_Mesh2d_FeatureSizeMapControlFwd_Header
