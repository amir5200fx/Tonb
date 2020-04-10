#pragma once
#ifndef _HsModeler_Sail_Header
#define _HsModeler_Sail_Header

#include <HsModeler_Body.hxx>

namespace tnbLib
{

	class HsModeler_Sail
		: public HsModeler_Body
	{

		/*Private Data*/

	public:

		HsModeler_Sail();

		HsModeler_Sail(const Standard_Integer theIndex);

		HsModeler_Sail(const Standard_Integer theIndex, const word& theName);
	};
}

#endif // !_HsModeler_Sail_Header
