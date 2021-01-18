#pragma once
#ifndef _HydStatic_CrsCurvesGraph_Header
#define _HydStatic_CrsCurvesGraph_Header

#include <Global_Done.hxx>
#include <HydStatic_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_CrsCurve;

	class HydStatic_CrsCurvesGraph
		: public HydStatic_Entity
		, public Global_Done
	{

		/*Private Data*/


		std::vector<std::shared_ptr<HydStatic_CrsCurve>> theCurves_;

		Standard_Real theMinDispv_;
		Standard_Real theMaxDispv_;


		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:

		HydStatic_CrsCurvesGraph()
		{}

		TnbHydStatic_EXPORT HydStatic_CrsCurvesGraph
		(
			const Standard_Integer theIndex, 
			const word& theName
		);


		const auto& Curves() const
		{
			return theCurves_;
		}

		auto MinDispv() const
		{
			return theMinDispv_;
		}

		auto MaxDispv() const
		{
			return theMaxDispv_;
		}

		TnbHydStatic_EXPORT void Perform
		(
			const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theUnClipped
		);
	};
}

#endif // !_HydStatic_CrsCurvesGraph_Header
