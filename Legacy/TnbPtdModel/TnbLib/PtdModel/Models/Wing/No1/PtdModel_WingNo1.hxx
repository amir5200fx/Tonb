#pragma once
#ifndef _PtdModel_WingNo1_Header
#define _PtdModel_WingNo1_Header

#include <PtdModel_Wing.hxx>

namespace tnbLib
{

	class PtdModel_WingNo1
		: public PtdModel_Wing
	{

		/*Private Data*/

		TnbPtdModel_EXPORT std::shared_ptr<PtdModel_WingExpandedView>
			CreateExpandView(const Standard_Integer, const PtdModel_WingSectionQ&) const override;

		TnbPtdModel_EXPORT std::vector<std::shared_ptr<PtdModel_WrappedWingSection>>
			CreateWrappedView() const override;

	protected:


		//- default constructor

		PtdModel_WingNo1()
		{}


	public:

		//- constructors

		PtdModel_WingNo1
		(
			const std::shared_ptr<PtdModel_WingGlobalPars>& pars
		)
			: PtdModel_Wing(pars)
		{}


		//- public functions and operators

	};
}

#endif // !_PtdModel_WingNo1_Header
