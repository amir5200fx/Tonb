#pragma once
#ifndef _MeshPost_QualityMap_Header
#define _MeshPost_QualityMap_Header

#include <MeshPost_Module.hxx>
#include <MeshPost_QualityMapTraits.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	template<class MetricMap>
	class MeshPost_QualityMap
	{

		/*Private Data*/

		std::shared_ptr<MetricMap> theMetrics_;

	public:

		typedef typename meshPostLib::quality_map_traits<MetricMap>::elemType elemType;

		// default constructor [9/19/2022 Amir]

		MeshPost_QualityMap()
		{}


		// constructors [9/19/2022 Amir]

		explicit MeshPost_QualityMap(const std::shared_ptr<MetricMap>& theMetrics)
			: theMetrics_(theMetrics)
		{}

		MeshPost_QualityMap(std::shared_ptr<MetricMap>&& theMetrics)
			: theMetrics_(std::move(theMetrics))
		{}

		// public functions and operators [9/19/2022 Amir]

		const auto& Metrics() const
		{
			return theMetrics_;
		}

		virtual Standard_Real CalcQuality(const elemType&) const = 0;

		void SetMetrics(const std::shared_ptr<MetricMap>& theMetrics)
		{
			theMetrics_ = theMetrics;
		}

		void SetMetrics(std::shared_ptr<MetricMap>&& theMetrics)
		{
			theMetrics_ = std::move(theMetrics);
		}
	};
}

#include <MeshPost2d_QualityMapSurface.hxx>

#endif // !_MeshPost_QualityMap_Header
