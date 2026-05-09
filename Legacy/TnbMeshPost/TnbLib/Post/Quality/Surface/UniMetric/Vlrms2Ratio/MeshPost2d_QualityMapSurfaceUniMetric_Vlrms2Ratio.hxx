#pragma once
#ifndef _MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio_Header
#define _MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio_Header

#include <MeshPost2d_QualityMapSurfaceUniMetric.hxx>

namespace tnbLib
{

	class MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio
		: public MeshPost2d_QualityMapSurfaceUniMetric
	{

		/*Private Data*/

	public:

		// default constructor [9/18/2022 Amir]

		MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio()
		{}


		// constructors [9/18/2022 Amir]

		explicit MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio
		(
			const std::shared_ptr<Aft2d_MetricPrcsrSurfaceUniMetric>& theMetrics
		)
			: MeshPost2d_QualityMapSurfaceUniMetric(theMetrics)
		{}

		MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio
		(
			std::shared_ptr<Aft2d_MetricPrcsrSurfaceUniMetric>&& theMetrics
		)
			: MeshPost2d_QualityMapSurfaceUniMetric(std::move(theMetrics))
		{}


		// public functions and operators [9/18/2022 Amir]

		TnbMeshPost_EXPORT Standard_Real
			CalcQuality(const Aft2d_ElementSurface&) const override;
	};
}

#endif // !_MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio_Header
