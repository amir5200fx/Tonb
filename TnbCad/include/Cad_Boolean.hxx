#pragma once
#ifndef _Cad_Boolean_Header
#define _Cad_Boolean_Header

class TopoDS_Shape;

namespace tnbLib
{

	class Cad_Boolean
	{

	public:

		static TopoDS_Shape 
			Union
			(
				const TopoDS_Shape& theShape0,
				const TopoDS_Shape& theShape1
			);

		static TopoDS_Shape 
			Subtract
			(
				const TopoDS_Shape& theTarget,
				const TopoDS_Shape& theShape
			);

		static TopoDS_Shape 
			Intersection
			(
				const TopoDS_Shape& theShape0, 
				const TopoDS_Shape& theShape1
			);

	};
}

#endif // !_Cad_Boolean_Header
