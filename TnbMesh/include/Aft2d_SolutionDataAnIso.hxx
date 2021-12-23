#pragma once
#ifndef _Aft2d_SolutionDataAnIso_Header
#define _Aft2d_SolutionDataAnIso_Header

#include <Aft2d_SolutionDataBase.hxx>
#include <Aft2d_MetricPrcsrAnIsoFwd.hxx>
#include <Aft2d_RegionPlaneAnIsoFwd.hxx>
#include <Aft2d_SegmentEdgeAnIsoFwd.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_InfoFwd.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Geo2d_MetricFunction.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Aft_MetricPrcsrAnIso_Info;

	class Aft2d_SolutionDataAnIso
		: public Aft2d_SolutionDataBase
	{

		/*Private Data*/

		std::shared_ptr<Aft_MetricPrcsrAnIso_Info> theGlobalMetricInfo_;
		std::shared_ptr<Geo2d_MetricFunction> theMetricFunction_;

		// Results [12/1/2021 Amir]

		std::shared_ptr<Aft2d_BoundaryOfPlaneAnIso_Info> theBoundaryInfo_;

		std::shared_ptr<Aft2d_RegionPlaneAnIso> theRegion_;
		std::shared_ptr<Aft2d_MetricPrcsrAnIso> theMetric_;

		std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>> theEdges_;

		std::vector<std::shared_ptr<Aft2d_ElementAnIso>> theElements_;

		// private functions and operators [12/1/2021 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:


		// default constructor [12/1/2021 Amir]

		Aft2d_SolutionDataAnIso()
		{}


		//- constructors


		// public functions and operators [12/1/2021 Amir]

		Standard_Boolean IsAnIso() const override
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

		const auto& MetricFunction() const
		{
			return theMetricFunction_;
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

		const auto& Elements() const
		{
			return theElements_;
		}

		void SetRegion(const std::shared_ptr<Aft2d_RegionPlaneAnIso>& theRegion)
		{
			theRegion_ = theRegion;
		}

		void SetRegion(std::shared_ptr<Aft2d_RegionPlaneAnIso>&& theRegion)
		{
			theRegion_ = std::move(theRegion);
		}

		void SetBoundaryInfo(const std::shared_ptr<Aft2d_BoundaryOfPlaneAnIso_Info>& theInfo)
		{
			theBoundaryInfo_ = theInfo;
		}

		void SetBoundaryInfo(std::shared_ptr<Aft2d_BoundaryOfPlaneAnIso_Info>&& theInfo)
		{
			theBoundaryInfo_ = std::move(theInfo);
		}

		void SetBoundaryEdges(const std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>& theBoundaries)
		{
			theEdges_ = theBoundaries;
		}

		void SetBoundaryEdges(std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>&& theBoundaries)
		{
			theEdges_ = std::move(theBoundaries);
		}

		void SetMetric(const std::shared_ptr<Aft2d_MetricPrcsrAnIso>& theMetric)
		{
			theMetric_ = theMetric;
		}

		void SetMetric(std::shared_ptr<Aft2d_MetricPrcsrAnIso>&& theMetric)
		{
			theMetric_ = std::move(theMetric);
		}

		void SetElements(const std::vector<std::shared_ptr<Aft2d_ElementAnIso>>& theElements)
		{
			theElements_ = theElements;
		}

		void SetElements(std::vector<std::shared_ptr<Aft2d_ElementAnIso>>&& theElements)
		{
			theElements_ = std::move(theElements);
		}

		void LoadGlobalMetricInfo(const std::shared_ptr<Aft_MetricPrcsrAnIso_Info>& theInfo)
		{
			theGlobalMetricInfo_ = theInfo;
		}

		void LoadGlobalMetricInfo(std::shared_ptr<Aft_MetricPrcsrAnIso_Info>&& theInfo)
		{
			theGlobalMetricInfo_ = std::move(theInfo);
		}

		void SetMetricFunction(const std::shared_ptr<Geo2d_MetricFunction>& theFun)
		{
			theMetricFunction_ = theFun;
		}

		void SetMetricFunction(std::shared_ptr<Geo2d_MetricFunction>&& theFun)
		{
			theMetricFunction_ = std::move(theFun);
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_SolutionDataAnIso);

#endif // !_Aft2d_SolutionDataAnIso_Header
