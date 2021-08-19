#pragma once
#ifndef _PtdModel_BladeSections_Header
#define _PtdModel_BladeSections_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declaration
	class PtdModel_BladeSection;

	class PtdModel_BladeSections
	{

		/*Private Data*/

		std::vector<std::shared_ptr<PtdModel_BladeSection>> theSections_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_BladeSections()
		{}


		//- constructors

		PtdModel_BladeSections(const std::vector<std::shared_ptr<PtdModel_BladeSection>>& theSections)
			: theSections_(theSections)
		{}

		PtdModel_BladeSections(std::vector<std::shared_ptr<PtdModel_BladeSection>>&& theSections)
			: theSections_(std::move(theSections))
		{}


		//- public functions and operators

		auto NbSections() const
		{
			return (Standard_Integer)theSections_.size();
		}

		const auto& Sections() const
		{
			return theSections_;
		}

		void SetSections(const std::vector<std::shared_ptr<PtdModel_BladeSection>>& theSections)
		{
			theSections_ = theSections;
		}

		void SetSections(std::vector<std::shared_ptr<PtdModel_BladeSection>>&& theSections)
		{
			theSections_ = std::move(theSections);
		}
	};
}

#endif // !_PtdModel_BladeSections_Header
