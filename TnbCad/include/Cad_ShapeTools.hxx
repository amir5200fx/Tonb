#pragma once
#ifndef _Cad_ShapeTools_Header
#define _Cad_ShapeTools_Header

#include <Pnt3d.hxx>
#include <Cad_Module.hxx>

class TopoDS_Shape;
class gp_Ax2;

namespace tnbLib
{

	class Cad_ShapeTools
	{

	public:

		static TnbCad_EXPORT TopoDS_Shape
			Box
			(
				const Pnt3d& theP0, 
				const Pnt3d& theP1
			);

		static TnbCad_EXPORT TopoDS_Shape
			Box
			(
				const Pnt3d& theP0,
				const Standard_Real dx,
				const Standard_Real dy, 
				const Standard_Real dz
			);

		static TnbCad_EXPORT TopoDS_Shape
			Box
			(
				const gp_Ax2& theAx, 
				const Standard_Real dx, 
				const Standard_Real dy, 
				const Standard_Real dz
			);

		static TnbCad_EXPORT TopoDS_Shape
			Cylinder
			(
				const gp_Ax2& theAx,
				const Standard_Real theR,
				const Standard_Real theH
			);

		static TnbCad_EXPORT TopoDS_Shape
			Cylinder
			(
				const gp_Ax2& theAx,
				const Standard_Real theR, 
				const Standard_Real theH,
				const Standard_Real theAngle
			);

		static TnbCad_EXPORT TopoDS_Shape
			Sphere
			(
				const Pnt3d& theC, 
				const Standard_Real theR
			);

		static TnbCad_EXPORT TopoDS_Shape
			Sphere
			(
				const gp_Ax2& theAx,
				const Standard_Real theR
			);

		static TnbCad_EXPORT TopoDS_Shape
			Sphere
			(
				const gp_Ax2& theAx,
				const Standard_Real theR, 
				const Standard_Real theAngle1
			);

		static TnbCad_EXPORT TopoDS_Shape
			Sphere
			(
				const gp_Ax2& theAx,
				const Standard_Real theR,
				const Standard_Real theAngle1,
				const Standard_Real theAngle2
			);

		static TnbCad_EXPORT TopoDS_Shape
			Sphere
			(
				const gp_Ax2& theAx, 
				const Standard_Real theR, 
				const Standard_Real theAngle1,
				const Standard_Real theAngle2,
				const Standard_Real theAngle3
			);
	};
}

#endif // !_Cad_ShapeTools_Header
