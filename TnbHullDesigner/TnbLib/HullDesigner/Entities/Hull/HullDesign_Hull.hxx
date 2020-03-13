#pragma once
#ifndef _HullDesign_Hull_Header
#define _HullDesign_Hull_Header

#include <Global_AccessMethod.hxx>
#include <HullDesign_Entity.hxx>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	class HullDesign_Hull
		: public HullDesign_Entity
	{

		/*Private Data*/

		TopoDS_Shape theShape_;

	public:

		HullDesign_Hull();

		HullDesign_Hull(const Standard_Integer theIndex);

		HullDesign_Hull(const Standard_Integer theIndex, const word& theName);

		//- Macros
		GLOBAL_ACCESS_SINGLE(TopoDS_Shape, Shape)

	};
}

#endif // !_HullDesign_Hull_Header
