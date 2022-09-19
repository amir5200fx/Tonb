#pragma once
#ifndef _MeshPost_LaplacianSmoothing_Header
#define _MeshPost_LaplacianSmoothing_Header

#include <MeshPost_QualityMap.hxx>
#include <MeshPost_LaplacianSmoothing_Traits.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [9/17/2022 Amir]
	template<class MetricMap>
	class MeshPost_LaplacianSmoothing_AvgFun;

	class MeshPost_LaplacianSmoothing_Info;

	template<class MetricMap>
	class MeshPost_LaplacianSmoothing
		: public Global_Done
	{

	public:

		typedef typename meshPostLib::laplacian_smoothing_traits<MetricMap>::elemType elemType;
		typedef typename meshPostLib::laplacian_smoothing_traits<MetricMap>::nodeType nodeType;

	private:

		/*Private Data*/

		std::shared_ptr<MeshPost_QualityMap<MetricMap>> theQualityFun_;
		std::shared_ptr<MeshPost_LaplacianSmoothing_AvgFun<MetricMap>> theAvgFun_;

		std::shared_ptr<MeshPost_LaplacianSmoothing_Info> theInfo_;

		std::shared_ptr<std::vector<std::shared_ptr<nodeType>>> theNodes_;

		// private functions and operators [9/18/2022 Amir]

		Standard_Real CalcWorstQuality(const nodeType&) const;

	public:

		static unsigned short verbose;

		// default constructor [9/17/2022 Amir]

		MeshPost_LaplacianSmoothing()
		{}

		// constructors [9/17/2022 Amir]


		// public functions and operators [9/17/2022 Amir]

		const auto& AvgFun() const
		{
			return theAvgFun_;
		}
		
		const auto& QualityFun() const
		{
			return theQualityFun_;
		}

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		const auto& Nodes() const
		{
			return theNodes_;
		}

		void Perform();

		void SetAvgFun(const std::shared_ptr<MeshPost_LaplacianSmoothing_AvgFun<MetricMap>>& theFun)
		{
			theAvgFun_ = theFun;
		}

		void SetAvgFun(std::shared_ptr<MeshPost_LaplacianSmoothing_AvgFun<MetricMap>>&& theFun)
		{
			theAvgFun_ = std::move(theFun);
		}

		void SetQualityFun(const std::shared_ptr<MeshPost_QualityMap<MetricMap>>& theQualityFun)
		{
			theQualityFun_ = theQualityFun;
		}

		void SetQualityFun(std::shared_ptr<MeshPost_QualityMap<MetricMap>>&& theQualityFun)
		{
			theQualityFun_ = std::move(theQualityFun);
		}

		void SetInfo(const std::shared_ptr<MeshPost_LaplacianSmoothing_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetInfo(std::shared_ptr<MeshPost_LaplacianSmoothing_Info>&& theInfo)
		{
			theInfo_ = std::move(theInfo);
		}

		void SetNodes(const std::shared_ptr<std::vector<std::shared_ptr<nodeType>>>& theNodes)
		{
			theNodes_ = theNodes;
		}

		void SetNodes(std::shared_ptr<std::vector<std::shared_ptr<nodeType>>>&& theNodes)
		{
			theNodes_ = std::move(theNodes);
		}
	};
}

#include <MeshPost_LaplacianSmoothingI.hxx>

#endif // !_MeshPost_LaplacianSmoothing_Header
