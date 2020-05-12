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

		Marine_HullBody
		(
			const Standard_Integer theIndex
		);

		Marine_HullBody
		(
			const Standard_Integer theIndex,
			const word& theName
		);


		Standard_Boolean IsHull() const override
		{
			return Standard_True;
		}

		Standard_Boolean IsLaunched() const;

		virtual Standard_Boolean IsWetted() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsDry() const
		{
			return Standard_False;
		}

	};
}

#endif // !_Marine_HullBody_Header
