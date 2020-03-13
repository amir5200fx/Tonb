#pragma once
#ifndef _Marine_HullBody_Header
#define _Marine_HullBody_Header

#include <Marine_Body.hxx>

namespace tnbLib
{

	class Marine_HullBody
		: public Marine_Body
	{

		/*Private Data*/

	public:

		Marine_HullBody();

		Marine_HullBody(const Standard_Integer theIndex);

		Marine_HullBody(const Standard_Integer theIndex, const word& theName);
	};
}

#endif // !_Marine_HullBody_Header
