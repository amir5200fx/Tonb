#pragma once
#ifndef _PtdModel_WingSection_Header
#define _PtdModel_WingSection_Header

#include <PtdModel_WingEntity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_WingSectionQ;
	class PtdModel_WingInfo;
	class PtdModel_xPars;
	class PtdModel_Wing;

	class PtdModel_WingSection
		: public PtdModel_WingEntity
	{

		/*Private Data*/

	protected:

		//- default constructor

		PtdModel_WingSection()
		{}


		//- constructors


		//- protected functions and operators

		static TnbPtdModel_EXPORT const std::shared_ptr<PtdModel_WingInfo>& WingInfo(const PtdModel_Wing&);
		static TnbPtdModel_EXPORT const std::shared_ptr<PtdModel_xPars>& xParameters(const PtdModel_Wing&);

	public:

		//- public functions and operators

		virtual std::shared_ptr<PtdModel_WingSectionQ> SectionQ(const Standard_Integer, const PtdModel_Wing&) const = 0;
	};
}

#endif // !_PtdModel_WingSection_Header
