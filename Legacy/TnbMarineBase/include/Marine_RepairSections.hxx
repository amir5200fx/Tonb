#pragma once
#ifndef _Marine_RepairSections_Header
#define _Marine_RepairSections_Header

#include <Global_Done.hxx>
#include <Marine_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class MarineRepairSect_AnalyzBody;
	class MarineRepairSect_FixedBody;
	class MarineRepairSect_CmpSection;

	class Marine_RepairSections
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<MarineRepairSect_AnalyzBody> theBody_;

		std::shared_ptr<MarineRepairSect_FixedBody> theFixed_;


		//- private functions and operators


	public:

		//- default constructor

		Marine_RepairSections()
		{}


		//- constructors

		Marine_RepairSections(const std::shared_ptr<MarineRepairSect_AnalyzBody>& theBody)
			: theBody_(theBody)
		{}

		Marine_RepairSections(std::shared_ptr<MarineRepairSect_AnalyzBody>&& theBody)
			: theBody_(std::move(theBody))
		{}


		//- public functions and operators

		const auto& Body() const
		{
			return theBody_;
		}

		const auto& FixedBody() const
		{
			return theFixed_;
		}

		TnbMarine_EXPORT void Perform();

		void LoadBody(const std::shared_ptr<MarineRepairSect_AnalyzBody>& theBody)
		{
			theBody_ = theBody;
		}

		void LoadBody(std::shared_ptr<MarineRepairSect_AnalyzBody>&& theBody)
		{
			theBody_ = std::move(theBody);
		}
	};
}

#endif // !_Marine_RepairSections_Header
