#pragma once
#ifndef _MeshPost_LaplacianSmoothing_AvgFun_Header
#define _MeshPost_LaplacianSmoothing_AvgFun_Header

#include <MeshPost_LaplacianSmoothing_AvgFunTraits.hxx>
#include <MeshPost_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <vector>
#include <map>

namespace tnbLib
{

	//  [9/17/2022 Amir]

	template<class MetricMap>
	class MeshPost_LaplacianSmoothing_AvgFun
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

	protected:

		// default constructor [9/17/2022 Amir]

		MeshPost_LaplacianSmoothing_AvgFun()
		{}

		// constructors [9/17/2022 Amir]


	public:

		typedef typename meshPostLib::laplacian_smoothing_avgFun_traits<MetricMap>::nodeType nodeType;
		typedef typename meshPostLib::laplacian_smoothing_avgFun_traits<MetricMap>::ptType Point;


		// public functions and operators [9/17/2022 Amir]

		const auto& Metrics() const
		{
			return theMetrics_;
		}

		virtual Point CalcAverage(const std::shared_ptr<nodeType>&) const = 0;

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

#endif // !_MeshPost2d_LaplacianSmoothing_AvgFun_Header
