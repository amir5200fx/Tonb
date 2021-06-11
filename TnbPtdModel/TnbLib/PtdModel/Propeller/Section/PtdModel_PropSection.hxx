#pragma once
#ifndef _PtdModel_PropSection_Header
#define _PtdModel_PropSection_Header

#include <PtdModel_PropEntity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_BladeSectionQ;
	class PtdModel_BladeInfo;
	class PtdModel_xPars;
	class PtdModel_PropBlade;

	class PtdModel_PropSection
		: public PtdModel_PropEntity
	{

		/*Private Data*/

	protected:

		//- default constructor

		PtdModel_PropSection()
		{}


		//- constructors


		//- protected functions and operators

		static TnbPtdModel_EXPORT const std::shared_ptr<PtdModel_BladeInfo>& BladeInfo(const PtdModel_PropBlade&);
		static TnbPtdModel_EXPORT const std::shared_ptr<PtdModel_xPars>& xParameters(const PtdModel_PropBlade&);

	public:

		//- public functions and operators

		virtual std::shared_ptr<PtdModel_BladeSectionQ> SectionQ(const Standard_Integer, const PtdModel_PropBlade&) const = 0;
	};
}

#endif // !_PtdModel_PropSection_Header
