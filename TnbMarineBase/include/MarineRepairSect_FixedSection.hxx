#pragma once
#ifndef _MarineRepairSect_FixedSection_Header
#define _MarineRepairSect_FixedSection_Header

#include <Marine_Entity.hxx>

#include <vector>

namespace tnbLib
{

	//- Forward Declarations
	class Pln_Curve;

	class MarineRepairSect_FixedSection
		: public Marine_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Pln_Curve>> theCurves_;

	public:

		//- default constructor

		MarineRepairSect_FixedSection()
		{}


		//- constructors

		MarineRepairSect_FixedSection(const std::vector<std::shared_ptr<Pln_Curve>>& theCurves)
			: theCurves_(theCurves)
		{}

		MarineRepairSect_FixedSection(std::vector<std::shared_ptr<Pln_Curve>>&& theCurves)
			: theCurves_(std::move(theCurves))
		{}

		MarineRepairSect_FixedSection
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::vector<std::shared_ptr<Pln_Curve>>& theCurves
		)
			: Marine_Entity(theIndex, theName)
			, theCurves_(theCurves)
		{}

		MarineRepairSect_FixedSection
		(
			const Standard_Integer theIndex,
			const word& theName, 
			std::vector<std::shared_ptr<Pln_Curve>>&& theCurves
		)
			: Marine_Entity(theIndex, theName)
			, theCurves_(std::move(theCurves))
		{}


		//- public functions and operators

		const auto& Curves() const
		{
			return theCurves_;
		}

		void SetCurves(const std::vector<std::shared_ptr<Pln_Curve>>& theCurves)
		{
			theCurves_ = theCurves;
		}

		void SetCurves(std::vector<std::shared_ptr<Pln_Curve>>&& theCurves)
		{
			theCurves_ = std::move(theCurves);
		}
	};
}

#endif // !_MarineRepairSect_FixedSection_Header
