#pragma once
#ifndef _MarineRepairSect_FixedBody_Header
#define _MarineRepairSect_FixedBody_Header

#include <Marine_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class MarineRepairSect_FixedSection;

	class MarineRepairSect_FixedBody
		: public Marine_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<MarineRepairSect_FixedSection>> theSections_;

	public:

		//- default constructor

		MarineRepairSect_FixedBody()
		{}


		//- constructors

		MarineRepairSect_FixedBody(const std::vector<std::shared_ptr<MarineRepairSect_FixedSection>>& theSections)
			: theSections_(theSections)
		{}

		MarineRepairSect_FixedBody(std::vector<std::shared_ptr<MarineRepairSect_FixedSection>>&& theSections)
			: theSections_(std::move(theSections))
		{}

		MarineRepairSect_FixedBody
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::vector<std::shared_ptr<MarineRepairSect_FixedSection>>& theSections
		)
			: Marine_Entity(theIndex, theName)
			, theSections_(theSections)
		{}

		MarineRepairSect_FixedBody
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			std::vector<std::shared_ptr<MarineRepairSect_FixedSection>>&& theSections
		)
			: Marine_Entity(theIndex, theName)
			, theSections_(std::move(theSections))
		{}


		//- public functions and operators

		const auto& Sections() const
		{
			return theSections_;
		}

		void SetSections(const std::vector<std::shared_ptr<MarineRepairSect_FixedSection>>& theSections)
		{
			theSections_ = theSections;
		}

		void SetSections(std::vector<std::shared_ptr<MarineRepairSect_FixedSection>>&& theSections)
		{
			theSections_ = std::move(theSections);
		}
	};
}

#endif // !_MarineRepairSect_FixedBody_Header
