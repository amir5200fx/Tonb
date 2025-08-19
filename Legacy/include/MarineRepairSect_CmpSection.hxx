#pragma once
#ifndef _MarineRepairSect_CmpSection_Header
#define _MarineRepairSect_CmpSection_Header

#include <Marine_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class MarineRepairSect_Section;
	class Pln_Curve;

	class MarineRepairSect_CmpSection
		: public Marine_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<MarineRepairSect_Section>> theSections_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMarine_EXPORT);

	public:

		//- default constructor

		MarineRepairSect_CmpSection()
		{}


		//- constructors

		MarineRepairSect_CmpSection(const std::vector<std::shared_ptr<MarineRepairSect_Section>>& theSections)
			: theSections_(theSections)
		{}

		MarineRepairSect_CmpSection(std::vector<std::shared_ptr<MarineRepairSect_Section>>&& theSections)
			: theSections_(std::move(theSections))
		{}

		MarineRepairSect_CmpSection
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const std::vector<std::shared_ptr<MarineRepairSect_Section>>& theSections
		)
			: Marine_Entity(theIndex, theName)
			, theSections_(theSections)
		{}

		MarineRepairSect_CmpSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<std::shared_ptr<MarineRepairSect_Section>>&& theSections
		)
			: Marine_Entity(theIndex, theName)
			, theSections_(std::move(theSections))
		{}


		//- public functions and operators

		const auto& Sections() const
		{
			return theSections_;
		}

		TnbMarine_EXPORT std::vector<std::shared_ptr<Pln_Curve>> FillingCurves() const;

		void SetSections(const std::vector<std::shared_ptr<MarineRepairSect_Section>>& theSections)
		{
			theSections_ = theSections;
		}

		void SetSections(std::vector<std::shared_ptr<MarineRepairSect_Section>>&& theSections)
		{
			theSections_ = std::move(theSections);
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::MarineRepairSect_CmpSection);

#endif // !_MarineRepairSect_CmpSection_Header
