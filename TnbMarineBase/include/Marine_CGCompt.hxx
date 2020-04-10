#pragma once
#ifndef _Marine_CGCompt_Header
#define _Marine_CGCompt_Header

#include <Marine_Entity.hxx>
#include <Global_AccessMethod.hxx>

namespace tnbLib
{

	class Marine_CGCompt
		: public Marine_Entity
	{

		/*Private Data*/

		Standard_Real theValue_;

	protected:

		Marine_CGCompt
		(
			const Standard_Real theValue
		);

		Marine_CGCompt
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const Standard_Real theValue
		);

	public:

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Value)
	};
}

#endif // !_Marine_CGCompt_Header
