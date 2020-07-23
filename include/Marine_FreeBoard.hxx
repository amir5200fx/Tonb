#pragma once
#ifndef _Marine_FreeBoard_Header
#define _Marine_FreeBoard_Header

#include <Marine_Entity.hxx>
#include <Global_AccessMethod.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	class Marine_FreeBoard
		: public Marine_Entity
	{

		/*Private Data*/

		Pnt3d theDP_;

		Standard_Real theF_;

	public:

		Marine_FreeBoard();

		Marine_FreeBoard(const Pnt3d& theDp, const Standard_Real theF);

		Marine_FreeBoard(const Standard_Integer theIndex, const word& theName, const Pnt3d& theDp, const Standard_Real theF);

		
		//- Macros
		GLOBAL_ACCESS_SINGLE(Pnt3d, DP)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, F)
	};
}

#endif // !_Marine_FreeBoard_Header
