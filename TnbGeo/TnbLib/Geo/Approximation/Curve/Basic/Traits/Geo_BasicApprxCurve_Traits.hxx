#pragma once
#ifndef _Geo_BasicApprxCurve_Traits_Header
#define _Geo_BasicApprxCurve_Traits_Header

#include <Geo_ApprxCurve_Traits.hxx>
#include <Geo3d_BasicApprxCurveAdaptorFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [8/25/2022 Amir]
	class Geo_BasicApprxCurve_Info;

	template<>
	struct Geo_ApprxCurve_Traits<Geo3d_BasicApprxCurveAdaptor>
	{
		typedef gp_Pnt ptType;
		typedef gp_Vec vtType;
	};

	template<>
	struct Geo_ApprxCurveInfo_Traits<Geo3d_BasicApprxCurveAdaptor>
	{
		typedef Geo_BasicApprxCurve_Info infoType;
	};


	template<class CurveType>
	struct Geo_BasicApprxCurveAdaptor_Traits
	{};

	template<>
	struct Geo_BasicApprxCurveAdaptor_Traits<Geom_Curve>
	{
		typedef gp_Pnt ptType;
	};

	namespace cascadeLib
	{

		template<> struct pt_type_from_curve<Geo3d_BasicApprxCurveAdaptor> { typedef Pnt3d ptType; };
	}
}

#endif // !_Geo_BasicApprxCurve_Traits_Header
