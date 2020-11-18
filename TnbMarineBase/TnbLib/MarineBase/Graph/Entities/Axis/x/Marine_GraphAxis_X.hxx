#pragma once
#ifndef _Marine_GraphAxis_X_Header
#define _Marine_GraphAxis_X_Header

#include <Marine_GraphAxis.hxx>

namespace tnbLib
{

	class Marine_GraphAxis_X
		: public Marine_GraphAxis
	{

		/*private Data*/

	public:

		TnbMarine_EXPORT Marine_GraphAxis_X();

		TnbMarine_EXPORT explicit Marine_GraphAxis_X
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_GraphAxis_X
		(
			const Standard_Integer theIndex,
			const word& theName
		);


		Standard_Boolean IsX() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_Marine_GraphAxis_X_Header
