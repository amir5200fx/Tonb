#pragma once
#ifndef _Marine_MidSectionApprox_Header
#define _Marine_MidSectionApprox_Header

#include <Global_Done.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Marine_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;

	class Marine_MidSectionApprox
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<marineLib::Body_Displacer> theBody_;

		std::shared_ptr<Marine_CmpSection> theSection_;

	protected:


		//- default constructor

		Marine_MidSectionApprox()
		{}


		//- constructors

		//- protected functions and operators

		auto& SectionRef()
		{
			return theSection_;
		}

	public:


		//- public functions and operators

		const auto& Section() const
		{
			return theSection_;
		}

		const auto& Body() const
		{
			return theBody_;
		}

		void LoadBody
		(
			const std::shared_ptr<marineLib::Body_Displacer>& theBody
		)
		{
			theBody_ = theBody;
		}
	};
}

#endif // !_Marine_MidSectionApprox_Header
