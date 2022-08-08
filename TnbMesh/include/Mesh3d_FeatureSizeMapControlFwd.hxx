#pragma once
#ifndef _Mesh3d_FeatureSizeMapControlFwd_Header
#define _Mesh3d_FeatureSizeMapControlFwd_Header

namespace tnbLib
{

	// Forward Declarations [7/18/2022 Amir]
	class Cad_TModel;

	template<class GeomType> class Mesh_FeatureSizeMapControl;

	typedef Mesh_FeatureSizeMapControl<Cad_TModel> Mesh3d_FeatureSizeMapControl;
}

#endif // !_Mesh3d_FeatureSizeMapControlFwd_Header
