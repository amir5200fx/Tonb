#pragma once
#ifndef _HydStatic_TankShape_Header
#define _HydStatic_TankShape_Header

#include <HydStatic_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_FillCurve;
	class HydStatic_CrsCurvesGraph;

	class HydStatic_TankShape
		: public HydStatic_Shape
	{

		/*Private Data*/

		std::shared_ptr<marineLib::Model_Tank> theTank_;


		std::shared_ptr<HydStatic_FillCurve> theFill_;
		std::shared_ptr<HydStatic_CrsCurvesGraph> theCross_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:

		//- default constructor

		HydStatic_TankShape()
		{}


		//- constructors

		TnbHydStatic_EXPORT HydStatic_TankShape
		(
			const std::shared_ptr<marineLib::Model_Tank>& theTank,
			const std::shared_ptr<HydStatic_FillCurve>& theFill,
			const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCross
		);

		TnbHydStatic_EXPORT HydStatic_TankShape
		(
			std::shared_ptr<marineLib::Model_Tank>&& theTank,
			std::shared_ptr<HydStatic_FillCurve>&& theFill,
			std::shared_ptr<HydStatic_CrsCurvesGraph>&& theCross
		);

		TnbHydStatic_EXPORT HydStatic_TankShape
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<marineLib::Model_Tank>& theTank,
			const std::shared_ptr<HydStatic_FillCurve>& theFill,
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
			const std::shared_ptr<HydStatic_FillCurve>& theCurve
		)
		{
			theFill_ = theCurve;
		}

		void SetFillCurve
		(
			std::shared_ptr<HydStatic_FillCurve>&& theCurve
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
	};
}

#endif // !_HydStatic_TankShape_Header
