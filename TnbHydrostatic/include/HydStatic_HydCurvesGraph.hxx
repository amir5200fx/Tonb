#pragma once
#ifndef _HydStatic_HydCurvesGraph_Header
#define _HydStatic_HydCurvesGraph_Header

#include <Global_Done.hxx>
#include <HydStatic_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_HydGphCurve;

	class HydStatic_HydCurvesGraph
		: public HydStatic_Entity
		, public Global_Done
	{

		/*Private Data*/

		std::vector<std::shared_ptr<HydStatic_HydGphCurve>> theCurves_;

		Standard_Real theTmin_;
		Standard_Real theTmax_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:

		HydStatic_HydCurvesGraph()
		{}

		TnbHydStatic_EXPORT HydStatic_HydCurvesGraph
		(
			const Standard_Integer theIndex, 
			const word& theName
		);


		auto Tmin() const
		{
			return theTmin_;
		}

		auto Tmax() const
		{
			return theTmax_;
		}

		TnbHydStatic_EXPORT void Perform
		(
			std::vector<std::shared_ptr<HydStatic_HydGphCurve>>&& theCurves
		);

		
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_HydCurvesGraph);

#endif // !_HydStatic_HydCurvesGraph_Header
