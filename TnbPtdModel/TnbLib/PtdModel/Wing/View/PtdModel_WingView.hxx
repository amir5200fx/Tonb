#pragma once
#ifndef _PtdModel_WingView_Header
#define _PtdModel_WingView_Header

#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_WingExpandedView;
	class PtdModel_WrappedWingSection;

	class PtdModel_WingView
	{

		/*Private Data*/

		std::vector<std::shared_ptr<PtdModel_WingExpandedView>> theExpandedViews_;
		std::vector<std::shared_ptr<PtdModel_WrappedWingSection>> theWrappedSections_;


	public:

		//- default constructor

		PtdModel_WingView()
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

		inline void SetExpandedViews(std::vector<std::shared_ptr<PtdModel_WingExpandedView>>&&);
		inline void SetWrappedSections(std::vector<std::shared_ptr<PtdModel_WrappedWingSection>>&&);
	};
}

#include <PtdModel_WingViewI.hxx>

#endif // !_PtdModel_WingView_Header
