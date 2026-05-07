#pragma once
#ifndef _Marine_RepairSection_Header
#define _Marine_RepairSection_Header

#include <Global_Done.hxx>
#include <Marine_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class MarineRepairSect_Section;
	class Pln_Curve;

	class Marine_RepairSection
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<MarineRepairSect_Section> theSection_;


		std::vector<std::shared_ptr<Pln_Curve>> theCurves_;

	public:

		//- default constructor

		Marine_RepairSection()
		{}


		//- public functions and operators

		Marine_RepairSection(const std::shared_ptr<MarineRepairSect_Section>& theSect)
			: theSection_(theSect)
		{}


		//- public functions and operators

		const auto& Section() const
		{
			return theSection_;
		}

		const auto& Curves() const
		{
			return theCurves_;
		}

		TnbMarine_EXPORT void Perform();

		void LoadSection(const std::shared_ptr<MarineRepairSect_Section>& theSect)
		{
			theSection_ = theSect;
		}

	};
}

#endif // !_Marine_RepairSection_Header
