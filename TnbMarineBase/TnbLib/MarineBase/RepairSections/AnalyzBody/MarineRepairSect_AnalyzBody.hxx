#pragma once
#ifndef _MarineRepairSect_AnalyzBody_Header
#define _MarineRepairSect_AnalyzBody_Header

#include <Marine_Entity.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// FOrward Declarations
	class MarineRepairSect_AnalyzSection;

	class MarineRepairSect_AnalyzBody
		: public Marine_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<MarineRepairSect_AnalyzSection>> theSections_;


	public:

		//- default constructor

		MarineRepairSect_AnalyzBody()
		{}


		//- constructors

		MarineRepairSect_AnalyzBody
		(
			const std::vector<std::shared_ptr<MarineRepairSect_AnalyzSection>>& theSections
		)
			: theSections_(theSections)
		{}

		MarineRepairSect_AnalyzBody
		(
			std::vector<std::shared_ptr<MarineRepairSect_AnalyzSection>>&& theSections
		)
			: theSections_(std::move(theSections))
		{}

		MarineRepairSect_AnalyzBody
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::vector<std::shared_ptr<MarineRepairSect_AnalyzSection>>& theSections
		)
			: Marine_Entity(theIndex, theName)
			, theSections_(theSections)
		{}

		MarineRepairSect_AnalyzBody
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<std::shared_ptr<MarineRepairSect_AnalyzSection>>&& theSections
		)
			: Marine_Entity(theIndex, theName)
			, theSections_(std::move(theSections))
		{}


		//- public functions and operators

		const auto& Sections() const
		{
			return theSections_;
		}

		auto& SectionsRef()
		{
			return theSections_;
		}

		TnbMarine_EXPORT Standard_Boolean HasDefectSection() const;
		TnbMarine_EXPORT Standard_Integer CalcNbDefectSections() const;

		void SetSections(const std::vector<std::shared_ptr<MarineRepairSect_AnalyzSection>>& theSections)
		{
			theSections_ = theSections;
		}

		void SetSections(std::vector<std::shared_ptr<MarineRepairSect_AnalyzSection>>&& theSections)
		{
			theSections_ = std::move(theSections);
		}
	};
}

#endif // !_MarineRepairSect_AnalyzBody_Header
