#pragma once
#ifndef _Aft2d_SolutionData_Header
#define _Aft2d_SolutionData_Header

#include <Aft2d_SolutionDataBase.hxx>
#include <Aft2d_MetricPrcsrFwd.hxx>
#include <Aft2d_RegionPlaneFwd.hxx>
#include <Aft2d_SegmentEdgeFwd.hxx>
#include <Aft2d_BoundaryOfPlane_InfoFwd.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Aft_MetricPrcsr_Info;
	class Mesh_Curve_Info;

	class Aft2d_SolutionData
		: public Aft2d_SolutionDataBase
	{

		/*Private Data*/

		std::shared_ptr<Aft_MetricPrcsr_Info> theGlobalMetricInfo_;


		// Results [12/1/2021 Amir]

		std::shared_ptr<Aft2d_BoundaryOfPlane_Info> theBoundaryInfo_;

		std::shared_ptr<Aft2d_MetricPrcsr> theMetric_;
		std::shared_ptr<Aft2d_RegionPlane> theRegion_;

		std::vector<std::shared_ptr<Aft2d_SegmentEdge>> theEdges_;

		// Private functions and operators [12/1/2021 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		// default constructor [12/1/2021 Amir]

		Aft2d_SolutionData()
		{}


		// constructors [12/1/2021 Amir]


		// public functions and operators [12/1/2021 Amir]

		Standard_Boolean IsIso() const override
		{
			return Standard_True;
		}

		auto HasBoundaryInfo() const
		{
			return (Standard_Boolean)theBoundaryInfo_;
		}

		const auto& GlobalMetricInfo() const
		{
			return theGlobalMetricInfo_;
		}

		const auto& Metric() const
		{
			return theMetric_;
		}

		const auto& BoundaryInfo() const
		{
			return theBoundaryInfo_;
		}

		const auto& BoundaryEdges() const
		{
			return theEdges_;
		}

		const auto& Region() const
		{
			return theRegion_;
		}

		void SetRegion(const std::shared_ptr<Aft2d_RegionPlane>& theRegion)
		{
			theRegion_ = theRegion;
		}

		void SetRegion(std::shared_ptr<Aft2d_RegionPlane>&& theRegion)
		{
			theRegion_ = std::move(theRegion);
		}

		void SetBoundaryInfo(const std::shared_ptr<Aft2d_BoundaryOfPlane_Info>& theInfo)
		{
			theBoundaryInfo_ = theInfo;
		}

		void SetBoundaryInfo(std::shared_ptr<Aft2d_BoundaryOfPlane_Info>&& theInfo)
		{
			theBoundaryInfo_ = std::move(theInfo);
		}

		void SetBoundaryEdges(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>& theBoundaries)
		{
			theEdges_ = theBoundaries;
		}

		void SetBoundaryEdges(std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&& theBoundaries)
		{
			theEdges_ = std::move(theBoundaries);
		}

		void SetMetric(const std::shared_ptr<Aft2d_MetricPrcsr>& theMetric)
		{
			theMetric_ = theMetric;
		}

		void SetMetric(std::shared_ptr<Aft2d_MetricPrcsr>&& theMetric)
		{
			theMetric_ = std::move(theMetric);
		}

		void LoadGlobalMetricInfo(const std::shared_ptr<Aft_MetricPrcsr_Info>& theInfo)
		{
			theGlobalMetricInfo_ = theInfo;
		}

		void LoadGlobalMetricInfo(std::shared_ptr<Aft_MetricPrcsr_Info>&& theInfo)
		{
			theGlobalMetricInfo_ = std::move(theInfo);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_SolutionData);

#endif // !_Aft2d_SolutionData_Header
