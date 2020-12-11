#pragma once
#ifndef _Cad_Boolean_Header
#define _Cad_Boolean_Header

#include <Cad_Module.hxx>

class TopoDS_Shape;

namespace tnbLib
{

	class Cad_Boolean
	{

	public:

		static TnbCad_EXPORT TopoDS_Shape 
			Union
			(
				const TopoDS_Shape& theShape0,
				const TopoDS_Shape& theShape1
			);

		static TnbCad_EXPORT TopoDS_Shape
			Subtract
			(
				const TopoDS_Shape& theTarget,
				const TopoDS_Shape& theShape
			);

		static TnbCad_EXPORT TopoDS_Shape
			Intersection
			(
				const TopoDS_Shape& theShape0, 
				const TopoDS_Shape& theShape1
			);

	};
}

#endif // !_Cad_Boolean_Header
