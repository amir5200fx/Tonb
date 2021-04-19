#pragma once
#ifndef _HydStatic_HullShape_Header
#define _HydStatic_HullShape_Header

#include <HydStatic_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_CrsCurvesGraph;


	class HydStatic_HullShape
		: public HydStatic_Shape
	{

		/*Private Data*/

		std::shared_ptr<marineLib::Model_Hull> theHull_;

		std::shared_ptr<HydStatic_CrsCurvesGraph> theCross_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:


		//- default constructor

		HydStatic_HullShape()
		{}


		//- public functions and operators

		const auto& Hull() const
		{
			return theHull_;
		}

		const auto& CrossCurves() const
		{
			return theCross_;
		}

		void SetHull(const std::shared_ptr<marineLib::Model_Hull>& theHull)
		{
			theHull_ = theHull;
		}

		void SetCrossCurves(const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCross)
		{
			theCross_ = theCross;
		}

	};
}

#endif // !_HydStatic_HullShape_Header
