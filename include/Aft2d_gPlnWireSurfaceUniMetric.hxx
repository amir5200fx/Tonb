#pragma once
#ifndef _Aft2d_gPlnWireSurfaceUniMetric_Header
#define _Aft2d_gPlnWireSurfaceUniMetric_Header

#include <Mesh_Module.hxx>
#include <Mesh_PlnWire.hxx>
#include <Aft2d_gPlnWireSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/19/2022 Amir]
	class GModel_ParaWire;

	template<>
	template<>
	TnbMesh_EXPORT std::shared_ptr<GModel_ParaWire>
		Aft2d_gPlnWireSurfaceUniMetric::MakeOrignWire<GModel_ParaWire>
		(
			const std::shared_ptr<Aft2d_gPlnWireSurfaceUniMetric>&
			);

	template<>
	TnbMesh_EXPORT Entity2d_Box Aft2d_gPlnWireSurfaceUniMetric::CalcBoundingBox(const Aft2d_gPlnCurveSurfaceUniMetric&);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gPlnWireSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gPlnWireSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_gPlnWireSurfaceUniMetric_Header
