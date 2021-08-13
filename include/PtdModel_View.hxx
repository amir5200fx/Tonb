#pragma once
#ifndef _PtdModel_View_Header
#define _PtdModel_View_Header

#include <PtdModel_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Section;

	class PtdModel_View
	{

		/*Private Data*/

		std::vector<std::shared_ptr<PtdModel_Section>> theSections_;

	public:

		//- default constructor
		PtdModel_View()
		{}


		//- constructors


		//- public functions and operators

		const auto& Sections() const
		{
			return theSections_;
		}

		void SetSections(const std::vector<std::shared_ptr<PtdModel_Section>>&);
		void SetSections(std::vector<std::shared_ptr<PtdModel_Section>>&&);
	};
}

#endif // !_PtdModel_View_Header
