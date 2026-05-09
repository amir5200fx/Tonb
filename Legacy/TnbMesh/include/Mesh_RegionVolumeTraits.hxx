#pragma once
#ifndef _Mesh_RegionVolumeTraits_Header
#define _Mesh_RegionVolumeTraits_Header

namespace tnbLib
{

	// Forward Declarations [3/7/2023 Payvand]

	class Cad_TModel;
	class Cad_GModel;

	class TModel_Surface;
	class GModel_Surface;

	template<class SurfType> struct Mesh_RegionVolumeTraits {};

	template<> struct Mesh_RegionVolumeTraits<TModel_Surface> { typedef Cad_TModel volType; };
	template<> struct Mesh_RegionVolumeTraits<GModel_Surface> { typedef Cad_GModel volType; };

}

#endif // !_Mesh_RegionVolumeTraits_Header
