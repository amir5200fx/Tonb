#pragma once
#ifndef _Aft_BoundaryOfPlane_Header
#define _Aft_BoundaryOfPlane_Header

#include <Global_Done.hxx>
#include <Geo_MetricPrcsr.hxx>
#include <Aft_BoundaryOfPlane_Base.hxx>
#include <Aft_BoundaryOfPlane_Traits.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	template<class RegionType, class SizeFun, class MetricFun = void>
	class Aft_BoundaryOfPlane
	{

		/*Private Data*/


		//- private functions and operators


	public:

		
	};

	template<class RegionType, class SizeFun>
	class Aft_BoundaryOfPlane<RegionType, SizeFun, void>
		: public Aft_BoundaryOfPlane_Base<typename aft_boundary_of_plane_entity_type<RegionType>::type>
	{

		typedef Geo_MetricPrcsr<SizeFun> metricPrcsr;
		typedef typename aft_boundary_of_plane_info_type<RegionType>::type info;
		typedef typename aft_boundary_of_plane_entity_type<RegionType>::type bndType;
		typedef Aft_BoundaryOfPlane_Base<typename bndType::type> base;
		typedef typename RegionType::plnCurveType curveType;

		/*Private Data*/

		std::shared_ptr<metricPrcsr> theMetricPrcsr_;
		std::shared_ptr<info> theInfo_;

		std::shared_ptr<RegionType> thePlane_;


		std::vector<std::shared_ptr<bndType>> theBoundaries_;

		//- private functions and operators

		std::vector<std::shared_ptr<bndType>>& ChangeBoundaries()
		{
			return theBoundaries_;
		}

		void UpdateFront();

	public:

		Aft_BoundaryOfPlane(const std::shared_ptr<info>& theInfo)
			: theInfo_(theInfo)
		{}

		const std::shared_ptr<metricPrcsr>& MetricProcessor() const
		{
			return theMetricPrcsr_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		const std::shared_ptr<RegionType>& Plane() const
		{
			return thePlane_;
		}

		const std::vector<std::shared_ptr<bndType>>& Boundaries() const
		{
			return theBoundaries_;
		}

		void Perform();

		void LoadMetricProcessor(const std::shared_ptr<metricPrcsr>& thePrcsr)
		{
			theMetricPrcsr_ = thePrcsr;
		}

		void LoadPlane(const std::shared_ptr<RegionType>& thePlane)
		{
			thePlane_ = thePlane;
		}
	};
}

#include <Aft_BoundaryOfPlaneI.hxx>

#endif // !_Aft_BoundaryOfPlane_Header
