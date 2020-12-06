#pragma once
#ifndef _CadModel_Regular_Header
#define _CadModel_Regular_Header

#include <CadModel_Entity.hxx>

namespace tnbLib
{

	class CadModel_Regular
		: public CadModel_Entity
	{

		/*Private Data*/

	protected:

		CadModel_Regular()
		{}

		TnbCadModel_EXPORT CadModel_Regular(const Standard_Integer theIndex);

		TnbCadModel_EXPORT CadModel_Regular(const Standard_Integer theIndex, const word& theName);

	public:

		virtual ~CadModel_Regular()
		{}

		TnbCadModel_EXPORT void PerformToPreview() override;
	};
}

#endif // !_CadModel_Regular_Header
