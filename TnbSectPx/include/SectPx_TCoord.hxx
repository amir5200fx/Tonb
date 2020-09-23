#pragma once
#ifndef _SectPx_TCoord_Header
#define _SectPx_TCoord_Header

#include <SectPx_Coord.hxx>
#include <SectPx_ParentAdaptor.hxx>

namespace tnbLib
{

	class SectPx_TCoord
		: public SectPx_Coord
		/*, public SectPx_ParentAdaptor*/
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_TCoord(_Types&&... _Args)
			: SectPx_Coord(_Args...)
		{}

	public:


	};
}

#endif // !_SectPx_TCoord_Header
