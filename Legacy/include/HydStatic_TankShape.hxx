#pragma once
#ifndef _HydStatic_TankShape_Header
#define _HydStatic_TankShape_Header

#include <HydStatic_Shape.hxx>
#include <Marine_VesselParam_KG.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Domain;
	class HydStatic_TankCapacityCurveQ;
	class HydStatic_CrsCurvesGraph;

	class HydStatic_TankShape
		: public HydStatic_Shape
	{

		/*Private Data*/

		std::shared_ptr<marineLib::Model_Tank> theTank_;

		Standard_Real thePerc_;

		marineLib::KG theKg_;

		std::shared_ptr<Marine_Domain> theDomain_;
		std::shared_ptr<HydStatic_TankCapacityCurveQ> theFill_;
		std::shared_ptr<HydStatic_CrsCurvesGraph> theCross_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:

		static TnbHydStatic_EXPORT Standard_Real DEFAULT_PERC_VALUE;

		//- default constructor

		HydStatic_TankShape()
		{}


		//- constructors

		TnbHydStatic_EXPORT HydStatic_TankShape
		(
			const std::shared_ptr<marineLib::Model_Tank>& theTank,
			const std::shared_ptr<HydStatic_TankCapacityCurveQ>& theFill,
			const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCross
		);

		TnbHydStatic_EXPORT HydStatic_TankShape
		(
			std::shared_ptr<marineLib::Model_Tank>&& theTank,
			std::shared_ptr<HydStatic_TankCapacityCurveQ>&& theFill,
			std::shared_ptr<HydStatic_CrsCurvesGraph>&& theCross
		);

		TnbHydStatic_EXPORT HydStatic_TankShape
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<marineLib::Model_Tank>& theTank,
			const std::shared_ptr<HydStatic_TankCapacityCurveQ>& theFill,
			const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCross
		);


		//- public functions and operators

		const auto& Model() const
		{
			return theTank_;
		}

		const auto& FillCuvre() const
		{
			return theFill_;
		}

		const auto& CrossCurves() const
		{
			return theCross_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		auto FullnessPerc() const
		{
			return thePerc_;
		}

		TnbHydStatic_EXPORT Standard_Real Capacity() const;

		const auto& KG() const
		{
			return theKg_;
		}

		void SetModel
		(
			std::shared_ptr<marineLib::Model_Tank>&& theTank
		)
		{
			theTank_ = std::move(theTank);
		}

		void SetModel
		(
			const std::shared_ptr<marineLib::Model_Tank>& theTank
		)
		{
			theTank_ = theTank;
		}

		void SetFillCurve
		(
			const std::shared_ptr<HydStatic_TankCapacityCurveQ>& theCurve
		)
		{
			theFill_ = theCurve;
		}

		void SetFillCurve
		(
			std::shared_ptr<HydStatic_TankCapacityCurveQ>&& theCurve
		)
		{
			theFill_ = std::move(theCurve);
		}

		void SetCrossCurves
		(
			const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCurves
		)
		{
			theCross_ = theCurves;
		}

		void SetCrossCurves
		(
			std::shared_ptr<HydStatic_CrsCurvesGraph>&& theCurves
		)
		{
			theCross_ = std::move(theCurves);
		}

		void SetDomain
		(
			const std::shared_ptr<Marine_Domain>& theDomain
		)
		{
			theDomain_ = theDomain;
		}

		void SetDomain
		(
			std::shared_ptr<Marine_Domain>&& theDomain
		)
		{
			theDomain_ = std::move(theDomain);
		}

		TnbHydStatic_EXPORT void SetKG(const Standard_Real theKg);

		TnbHydStatic_EXPORT void SetFullnessPerc(const Standard_Real x);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_TankShape);

#endif // !_HydStatic_TankShape_Header
