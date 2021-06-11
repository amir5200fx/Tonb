#pragma once
#ifndef _PtdModel_PropBladeNo1_Header
#define _PtdModel_PropBladeNo1_Header

#include <PtdModel_PropBlade.hxx>

namespace tnbLib
{

	class PtdModel_PropBladeNo1
		: public PtdModel_PropBlade
	{

		/*Private Data*/


		//- private functions and operators

		std::shared_ptr<PtdModel_BladeExpandedView> CreateExpandView(const PtdModel_BladeSectionQ&) const override;
		
		std::vector<std::shared_ptr<PtdModel_UnWrappedBladeSection>> CreateUnWrappedView() const override;
		std::vector<std::shared_ptr<PtdModel_WrappedBladeSection>> CreateWrappedView() const override;


		//- default constructor

		PtdModel_PropBladeNo1()
		{}

	public:

		
		//- constructors

		PtdModel_PropBladeNo1(const std::shared_ptr<PtdModel_BladeGlobalPars>&);


		//- public functions and operators


	};
}

#endif // !_PtdModel_PropBladeNo1_Header

