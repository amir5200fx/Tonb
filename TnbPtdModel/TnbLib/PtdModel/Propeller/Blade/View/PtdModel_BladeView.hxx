#pragma once
#ifndef _PtdModel_BladeView_Header
#define _PtdModel_BladeView_Header

#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_BladeExpandedView;
	class PtdModel_WrappedBladeSection;
	class PtdModel_UnWrappedBladeSection;
	class PtdModel_BladeFace;

	class PtdModel_BladeView
	{

		/*Private Data*/

		std::vector<std::shared_ptr<PtdModel_BladeExpandedView>> theExpandedViews_;
		std::vector<std::shared_ptr<PtdModel_WrappedBladeSection>> theWrappedSections_;
		std::vector<std::shared_ptr<PtdModel_UnWrappedBladeSection>> theUnWrappedSections_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_BladeView()
		{}


		//- constructors


		//- public functions and operators


		const auto& ExpandedViews() const
		{
			return theExpandedViews_;
		}

		const auto& WrappedSections() const
		{
			return theWrappedSections_;
		}

		const auto& UnWrappedSections() const
		{
			return theUnWrappedSections_;
		}

		inline void SetExpandedViews(std::vector<std::shared_ptr<PtdModel_BladeExpandedView>>&&);
		inline void SetWrappedSections(std::vector<std::shared_ptr<PtdModel_WrappedBladeSection>>&&);
		inline void SetUnWrappedSections(std::vector<std::shared_ptr<PtdModel_UnWrappedBladeSection>>&&);

	};
}

#include <PtdModel_BladeViewI.hxx>

#endif // !_PtdModel_BladeView_Header
