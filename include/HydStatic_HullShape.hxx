#pragma once
#ifndef _HydStatic_HullShape_Header
#define _HydStatic_HullShape_Header

#include <HydStatic_Shape.hxx>
#include <Marine_VesselParam_KG.hxx>
#include <Marine_VesselParam_DISPV.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_CrsCurvesGraph;


	class HydStatic_HullShape
		: public HydStatic_Shape
	{

		/*Private Data*/

		marineLib::DISPV theDispv_;

		std::shared_ptr<marineLib::Model_Hull> theHull_;

		std::shared_ptr<HydStatic_CrsCurvesGraph> theCross_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:


		//- default constructor

		HydStatic_HullShape()
		{}


		//- public functions and operators

		const auto& DISPV() const
		{
			return theDispv_;
		}

		const auto& Hull() const
		{
			return theHull_;
		}

		const auto& CrossCurves() const
		{
			return theCross_;
		}

		TnbHydStatic_EXPORT void SetHull(const std::shared_ptr<marineLib::Model_Hull>& theHull);
		TnbHydStatic_EXPORT void SetHull(std::shared_ptr<marineLib::Model_Hull>&& theHull);

		TnbHydStatic_EXPORT void SetCrossCurves(const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCross);
		TnbHydStatic_EXPORT void SetCrossCurves(std::shared_ptr<HydStatic_CrsCurvesGraph>&& theCross);

		TnbHydStatic_EXPORT void SetDispv(const marineLib::DISPV& theV);
		TnbHydStatic_EXPORT void SetDispv(marineLib::DISPV&& theV);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_HullShape);

#endif // !_HydStatic_HullShape_Header
