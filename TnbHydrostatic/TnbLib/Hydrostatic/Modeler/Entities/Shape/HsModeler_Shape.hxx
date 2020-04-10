#pragma once
#ifndef _HsModeler_Shape_Header
#define _HsModeler_Shape_Header

#include <HsModeler_Entity.hxx>

#include <gp_Ax2.hxx>
#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	class HsModeler_Shape
		: public HsModeler_Entity
	{

		/*Private Data*/

		gp_Ax2 theSystem_;

		TopoDS_Shape theShape_;

	protected:

		HsModeler_Shape();

		HsModeler_Shape(const Standard_Integer theIndex);

		HsModeler_Shape(const Standard_Integer theIndex, const word& theName);

		void SetSystem(const gp_Ax2& theSystem);
	};
}

#endif // !_HsModeler_Shape_Header
