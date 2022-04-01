#pragma once
#ifndef _Cad_SingularZoneTraits_Header
#define _Cad_SingularZoneTraits_Header

namespace tnbLib
{

	template<class Surfpln>
	struct cad_singular_zone_traits
	{};

	// Forward Declarations [3/30/2022 Amir]
	class GModel_Plane;
	class TModel_Plane;

	class GModel_ParaCurve;
	class TModel_ParaCurve;

	template<>
	struct cad_singular_zone_traits<GModel_Plane>
	{
		typedef GModel_ParaCurve curveType;
	};

	template<>
	struct cad_singular_zone_traits<TModel_Plane>
	{
		typedef TModel_ParaCurve curveType;
	};
}

#endif // !_Cad_SingularZoneTraits_Header
