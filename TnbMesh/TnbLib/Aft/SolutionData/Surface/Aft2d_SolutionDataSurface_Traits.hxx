#pragma once
#ifndef _Aft2d_SolutionDataSurface_Traits_Header
#define _Aft2d_SolutionDataSurface_Traits_Header

namespace tnbLib
{

	// Forward Declarations [2/18/2022 Amir]
	class Cad_TModel;
	class Cad_GModel;
	class GModel_Plane;
	class TModel_Plane;

	template<class ShapeType>
	struct shape_plane_type_trait {};

	template<>
	struct shape_plane_type_trait<Cad_TModel> { typedef TModel_Plane type; };

	template<>
	struct shape_plane_type_trait<Cad_GModel> { typedef GModel_Plane type; };
}

#endif // !_Aft2d_SolutionDataSurface_Traits_Header
