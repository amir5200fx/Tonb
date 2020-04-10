#pragma once
#ifndef _HsModeler_Tank_Header
#define _HsModeler_Tank_Header

#include <HsModeler_Body.hxx>

namespace tnbLib
{

	class HsModeler_Tank
		: public HsModeler_Body
	{

		/*Private Data*/

	public:

		HsModeler_Tank();

		HsModeler_Tank(const Standard_Integer theIndex);

		HsModeler_Tank(const Standard_Integer theIndex, const word& theName);


	};
}

#endif // !_HsModeler_Tank_Header
