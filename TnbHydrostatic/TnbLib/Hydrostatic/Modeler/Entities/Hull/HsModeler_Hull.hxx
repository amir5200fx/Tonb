#pragma once
#ifndef _HsModeler_Hull_Header
#define _HsModeler_Hull_Header

#include <HsModeler_Body.hxx>

namespace tnbLib
{

	class HsModeler_Hull
		: public HsModeler_Body
	{

		/*Private Data*/

	public:

		HsModeler_Hull();

		HsModeler_Hull(const Standard_Integer theIndex);

		HsModeler_Hull(const Standard_Integer theIndex, const word& theName);
	};
}

#endif // !_HsModeler_Hull_Header
