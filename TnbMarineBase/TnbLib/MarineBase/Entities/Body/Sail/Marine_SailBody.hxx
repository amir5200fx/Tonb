#pragma once
#ifndef _Marine_SailBody_Header
#define _Marine_SailBody_Header

#include <Marine_Body.hxx>

namespace tnbLib
{

	class Marine_SailBody
		: public Marine_Body
	{

		/*Private Data*/

	public:

		Marine_SailBody();

		Marine_SailBody(const Standard_Integer theIndex);

		Marine_SailBody(const Standard_Integer theIndex, const word& theName);
	};
}

#endif // !_Marine_SailBody_Header
