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

		TnbPtdModel_EXPORT std::shared_ptr<PtdModel_BladeExpandedView> 
			CreateExpandView
			(
				const Standard_Integer section,
				const PtdModel_BladeSectionQ&
			) const override;
		
		TnbPtdModel_EXPORT std::vector<std::shared_ptr<PtdModel_UnWrappedBladeSection>> CreateUnWrappedView() const override;
		TnbPtdModel_EXPORT std::vector<std::shared_ptr<PtdModel_WrappedBladeSection>> CreateWrappedView() const override;


		//- default constructor

		PtdModel_PropBladeNo1()
		{}

	public:

		
		//- constructors

		TnbPtdModel_EXPORT PtdModel_PropBladeNo1(const std::shared_ptr<PtdModel_BladeGlobalPars>&);


		//- public functions and operators


	};
}

#endif // !_PtdModel_PropBladeNo1_Header

