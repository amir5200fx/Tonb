#pragma once
#ifndef _Cad_ApprxParaPlaneTraits_Header
#define _Cad_ApprxParaPlaneTraits_Header

namespace tnbLib
{

	template<class PlnType>
	struct cad_apprx_plane_traits{};

	// Forward Declarations [4/18/2022 Amir]
	class GModel_Plane;
	class TModel_Plane;
	class GModel_ParaWire;
	class TModel_ParaWire;

	template<>
	struct cad_apprx_plane_traits<GModel_Plane> { typedef GModel_ParaWire wireType; };

	template<>
	struct cad_apprx_plane_traits<TModel_Plane> { typedef TModel_ParaWire wireType; };
}

#endif // !_Cad_ApprxParaPlaneTraits_Header
