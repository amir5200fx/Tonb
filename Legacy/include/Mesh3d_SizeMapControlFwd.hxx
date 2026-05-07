#pragma once
#ifndef _Mesh3d_SizeMapControlFwd_Header
#define _Mesh3d_SizeMapControlFwd_Header

namespace tnbLib
{

	// Forward Declarations [6/22/2022 Amir]
	class Cad_TModel;

	template<class GeomType> class Mesh_SizeMapControl;

	typedef Mesh_SizeMapControl<Cad_TModel> Mesh3d_SizeMapControl;
}

#endif // !_Mesh3d_SizeMapControlFwd_Header
