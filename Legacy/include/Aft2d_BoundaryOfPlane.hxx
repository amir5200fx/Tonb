#pragma once
#ifndef _Aft2d_BoundaryOfPlane_Header
#define _Aft2d_BoundaryOfPlane_Header

#include <Aft_BoundaryOfPlane.hxx>
#include <Aft2d_BoundaryOfPlaneFwd.hxx>
#include <Geo2d_MetricPrcsr.hxx>

namespace tnbLib
{

	template<>
	class Aft_BoundaryOfPlane<Aft2d_RegionPlane, Geo2d_SizeFunction>
		: public Aft_BoundaryOfPlane_Base<Aft2d_SegmentEdge>
	{

		/*Private Data*/

		std::shared_ptr<Geo2d_MetricPrcsr> theMetricPrscr_;
		std::shared_ptr<Aft2d_BoundaryOfPlane_Info> theInfo_;

		std::shared_ptr<Aft2d_RegionPlane> thePlane_;


		std::vector<std::shared_ptr<Aft2d_SegmentEdge>> theSegments_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

		auto& BoundariesRef()
		{
			return theSegments_;
		}


		TnbMesh_EXPORT void UpdateFront();


		//- default constructor

		Aft_BoundaryOfPlane()
		{}

	public:


		static TnbMesh_EXPORT unsigned short verbose;

		//- constructors

		Aft_BoundaryOfPlane
		(
			const std::shared_ptr<Aft2d_BoundaryOfPlane_Info>& theInfo
		)
			: theInfo_(theInfo)
		{}


		//- public functions and operators

		const auto& MetricProcessor() const
		{
			return theMetricPrscr_;
		}

		const auto& Info() const
		{
			return theInfo_;
		}

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& Boundaries() const
		{
			return theSegments_;
		}


		TnbMesh_EXPORT void Perform();

		void LoadMetricProcessor(const std::shared_ptr<Geo2d_MetricPrcsr>& thePrcsr)
		{
			theMetricPrscr_ = thePrcsr;
		}

		void LoadPlane(const std::shared_ptr<Aft2d_RegionPlane>& theRegion)
		{
			thePlane_ = theRegion;
		}
	};
}

#endif // !_Aft2d_BoundaryOfPlane_Header
