#pragma once
#ifndef _Pln_CascadeTools_Header
#define _Pln_CascadeTools_Header

#include <Cad2d_Module.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

class gp_Ax2d;
class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;

class Geom2d_Curve;


namespace tnbLib
{

	//- Forward Declarations
	class Pnt2d;

	class Pln_CascadeTools
	{

	public:

		static TnbCad2d_EXPORT gp_Circ2d 
			CreateCircle
			(
				const gp_Ax2d& theAx, 
				const Standard_Real theRadius
			);

		static TnbCad2d_EXPORT gp_Elips2d 
			CreateEllipse
			(
				const gp_Ax2d& theMajorAx,
				const Standard_Real theMajorRadius, 
				const Standard_Real theMinorRadius
			);

		static TnbCad2d_EXPORT gp_Hypr2d 
			CreateHyperbola
			(
				const gp_Ax2d& theMajorAxis, 
				const Standard_Real theMajorRadius,
				const Standard_Real theMinorRadius
			);

		static TnbCad2d_EXPORT gp_Parab2d 
			CreateParabola
			(
				const gp_Ax2d& theMirrorAxis, 
				const Standard_Real theFocalLength
			);

		static TnbCad2d_EXPORT gp_Parab2d 
			CreateParabola
			(
				const gp_Ax2d& theMirrorAxis,
				const Pnt2d& theFocus
			);

		static TnbCad2d_EXPORT std::pair<Pnt2d, Standard_Real>
			Project
			(
				const Pnt2d& thePnt,
				const Handle(Geom2d_Curve)&
			);
	};
}

#endif // !_Pln_CascadeTools_Header
