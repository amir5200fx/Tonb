#pragma once
#ifndef _HydStatic_GeomCrsCurvesGraph_Header
#define _HydStatic_GeomCrsCurvesGraph_Header

#include <HydStatic_CrsCurvesGraph.hxx>

namespace tnbLib
{

	class HydStatic_GeomCrsCurvesGraph
		: public HydStatic_CrsCurvesGraph
	{

		/* Private Data*/

		std::vector<std::shared_ptr<HydStatic_CrsCurve>> theCurves_;


		//- private functions and operators

		TnbHydStatic_EXPORT void Perform();


		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:

		//- default constructor

		HydStatic_GeomCrsCurvesGraph()
		{}


		//- constructors

		HydStatic_GeomCrsCurvesGraph
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

		TnbHydStatic_EXPORT void Perform(const std::vector<std::shared_ptr<HydStatic_CrsCurve>>&);
		TnbHydStatic_EXPORT void Perform(std::vector<std::shared_ptr<HydStatic_CrsCurve>>&&);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_GeomCrsCurvesGraph);

#endif // !_HydStatic_GeomCrsCurvesGraph_Header
