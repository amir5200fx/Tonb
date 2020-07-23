#pragma once
#ifndef _Marine_CoordinatedEntity_Header
#define _Marine_CoordinatedEntity_Header

#include <Marine_Entity.hxx>
#include <Global_AccessMethod.hxx>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	class Marine_CoordinatedEntity
		: public Marine_Entity
	{

		/*Private Data*/

		gp_Ax2 theCoordinateSystem_;

	protected:

		template<class... _Types>
		Marine_CoordinatedEntity(_Types&&... _Args)
			: Marine_Entity(_Args...)
		{}

	public:

		//- Macros
		GLOBAL_ACCESS_SINGLE(gp_Ax2, CoordinateSystem)
	};
}

#endif // !_Marine_CoordinatedEntity_Header
