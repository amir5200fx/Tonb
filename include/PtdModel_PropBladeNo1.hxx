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

		std::shared_ptr<PtdModel_BladeExpandedView> CreateExpandView(const std::vector<Pnt3d>& theTf, const std::vector<Pnt3d>& theTb) const override;
		
		void CreateUnWrappedView() const override;
		void CreateWrappedView() const override;

	public:

		//- default constructor

		PtdModel_PropBladeNo1()
		{}


		//- constructors


		//- public functions and operators


	};
}

#endif // !_PtdModel_PropBladeNo1_Header

