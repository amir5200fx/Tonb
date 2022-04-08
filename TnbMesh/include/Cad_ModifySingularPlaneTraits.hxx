#pragma once
#ifndef _Cad_ModifySingularPlaneTraits_Header
#define _Cad_ModifySingularPlaneTraits_Header

namespace tnbLib
{

	template<class SurfPlnType>
	struct cad_modify_singular_plane_traits {};

	// Forward Declarations [3/31/2022 Amir]
	class GModel_Plane;
	class TModel_Plane;
	class GModel_ParaCurve;
	class TModel_ParaCurve;
	class GModel_ParaWire;
	class TModel_ParaWire;

	template<>
	struct cad_modify_singular_plane_traits<GModel_Plane>
	{
		typedef GModel_ParaWire wireType;
		typedef GModel_ParaCurve curveType;
	};

	template<>
	struct cad_modify_singular_plane_traits<TModel_Plane>
	{
		typedef TModel_ParaWire wireType;
		typedef TModel_ParaCurve curveType;
	};
}

#endif // !_Cad_ModifySingularPlaneTraits_Header
