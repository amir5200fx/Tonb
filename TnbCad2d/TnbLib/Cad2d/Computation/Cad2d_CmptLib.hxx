#pragma once
#ifndef _Cad2d_CmptLib_Header
#define _Cad2d_CmptLib_Header

#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <Cad2d_Module.hxx>

class Geom2d_Curve;
class gp_Trsf2d;
class gp_Ax2d;

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_AdaptiveInteg_Info;
	class Pln_Wire;
	class Pnt2d;
	class Cad2d_Plane;

	class Cad2d_CmptLib
	{

	public:



		//- Check the convergence of the algorithm with the info parameter
		static TnbCad2d_EXPORT Standard_Real
			AreaUnderCurve
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			Mx
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			My
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			Ix
			(
				const Handle(Geom2d_Curve)& theCurve, 
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			Iy
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			Area
			(
				const Pln_Wire& theWire,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			DiscreteArea
			(
				const Pln_Wire& theWire
			);

		static TnbCad2d_EXPORT Standard_Real
			xCentreProductArea
			(
				const Handle(Geom2d_Curve)& theCurve,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			yCentreProductArea
			(
				const Handle(Geom2d_Curve)& theCurve,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Pnt2d
			Centre
			(
				const Handle(Geom2d_Curve)& theCurve,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Pnt2d
			Centre
			(
				const Pln_Wire& theWire,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		

		static TnbCad2d_EXPORT Standard_Real IxBar(const Pln_Wire& theWire, const Pnt2d& theCentre, const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo);

		static TnbCad2d_EXPORT Standard_Real IyBar(const Pln_Wire& theWire, const Pnt2d& theCentre, const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo);

		static TnbCad2d_EXPORT Standard_Real
			Mx
			(
				const Pln_Wire& theWire,
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			My
			(
				const Pln_Wire& theWire,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			Ix
			(
				const Pln_Wire& theWire, 
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			Iy
			(
				const Pln_Wire& theWire, 
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			xCentre
			(
				const Pln_Wire& theWire,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			yCentre
			(
				const Pln_Wire& theWire, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			xCentreProductArea
			(
				const Pln_Wire& theWire,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			yCentreProductArea
			(
				const Pln_Wire& theWire,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real 
			Area
			(
				const Cad2d_Plane& thePlane,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbCad2d_EXPORT Standard_Real
			DiscreteArea
			(
				const Cad2d_Plane& thePlane
			);

		static TnbCad2d_EXPORT Standard_Real Ixy(const Pln_Wire& theWire, const Pnt2d& theC, const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo);

		static TnbCad2d_EXPORT Standard_Real Iv(const Pln_Wire& theWire, const gp_Ax2d& theAx, const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo);

		static TnbCad2d_EXPORT gp_Trsf2d Transform(const gp_Ax2d& theCurrent, const gp_Ax2d& theTarget);
	};
}

#endif // !_Cad2d_CmptLib_Header
