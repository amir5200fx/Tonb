#pragma once
#ifndef _Cad2d_CmptLib_Header
#define _Cad2d_CmptLib_Header

#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>

class Geom2d_Curve;

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_AdaptiveInteg_Info;
	class Pln_Wire;
	class Pnt2d;

	class Cad2d_CmptLib
	{

	public:

		//- Check the convergence of the algorithm with the info parameter
		static Standard_Real
			AreaUnderCurve
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real 
			Area
			(
				const Pln_Wire& theWire,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real
			xCentreProductArea
			(
				const Handle(Geom2d_Curve)& theCurve,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real
			yCentreProductArea
			(
				const Handle(Geom2d_Curve)& theCurve,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Pnt2d
			Centre
			(
				const Handle(Geom2d_Curve)& theCurve,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real
			Centre
			(
				const Pln_Wire& theWire,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);
	};
}

#endif // !_Cad2d_CmptLib_Header
