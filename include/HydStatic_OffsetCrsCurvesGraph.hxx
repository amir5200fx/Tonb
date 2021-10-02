#pragma once
#ifndef _HydStatic_OffsetCrsCurvesGraph_Header
#define _HydStatic_OffsetCrsCurvesGraph_Header

#include <HydStatic_CrsCurvesGraph.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_CrsCurveQ;

	class HydStatic_OffsetCrsCurvesGraph
		: public HydStatic_CrsCurvesGraph
	{

		/* Private Data*/

		std::vector<std::shared_ptr<HydStatic_CrsCurveQ>> theCurves_;


		//- private function and operators

		TnbHydStatic_EXPORT void Perform();

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:

		//- default constructor

		HydStatic_OffsetCrsCurvesGraph()
		{}


		//- constructors

		HydStatic_OffsetCrsCurvesGraph
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: HydStatic_CrsCurvesGraph(theIndex, theName)
		{}


		//- public functions and operators

		TnbHydStatic_EXPORT Standard_Integer NbCurves() const override;
		TnbHydStatic_EXPORT hydStcLib::CurveMakerType CurveType() const override;

		const auto& Curves() const
		{
			return theCurves_;
		}

		TnbHydStatic_EXPORT std::vector<std::pair<LeverArm, Heel>> 
			RetrieveLeverArms(const Standard_Real x) const override;

		TnbHydStatic_EXPORT void Perform(const std::vector<std::shared_ptr<HydStatic_CrsCurveQ>>&);
		TnbHydStatic_EXPORT void Perform(std::vector<std::shared_ptr<HydStatic_CrsCurveQ>>&&);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_OffsetCrsCurvesGraph);

#endif // !_HydStatic_OffsetCrsCurvesGraph_Header
