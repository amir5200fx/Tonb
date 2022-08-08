#pragma once
#ifndef _Mesh3d_BoundarySizeMapControlFwd_Header
#define _Mesh3d_BoundarySizeMapControlFwd_Header

namespace tnbLib
{

	// Forward Declarations [6/22/2022 Amir]
	class Cad_TModel;

	template<class GeomType> class Mesh_BoundarySizeMapControl;

	typedef Mesh_BoundarySizeMapControl<Cad_TModel> Mesh3d_BoundarySizeMapControl;
}

#endif // !_Mesh3d_BoundarySizeMapControlFwd_Header
