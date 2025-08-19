#pragma once
#ifndef _MeshPost2d_QualityMapTemplate_Header
#define _MeshPost2d_QualityMapTemplate_Header

#include <MeshPost_Module.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>
#include <boost/serialization/serialization.hpp>

namespace tnbLib
{

	// Forward Declarations [9/17/2022 Amir]
	class Pnt2d;

	template<class MetricMap>
	class MeshPost2d_QualityMapTemplate
	{

		/*Private Data*/

		std::shared_ptr<MetricMap> theMetrics_;

		// Private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			// empty body
		}

	public:

		// default constructor [9/17/2022 Amir]

		MeshPost2d_QualityMapTemplate()
		{}


		// constructors [9/17/2022 Amir]

		explicit MeshPost2d_QualityMapTemplate(const std::shared_ptr<MetricMap>& theMetrics)
			: theMetrics_(theMetrics)
		{}

		MeshPost2d_QualityMapTemplate(std::shared_ptr<MetricMap>&& theMetrics)
			: theMetrics_(std::move(theMetrics))
		{}

		// public functions and operators [9/17/2022 Amir]

		const auto& Metrics() const
		{
			return theMetrics_;
		}

		virtual Standard_Real CalcQuality(const Pnt2d&, const Pnt2d&, const Pnt2d&) const = 0;

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

#endif // !_MeshPost2d_QualityMapTemplate_Header
