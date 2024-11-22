#pragma once
#ifndef _Cad_RailRevolve_Header
#define _Cad_RailRevolve_Header

#include <Cad_Module.hxx>
#include <Global_Done.hxx>
#include <Global_Handle.hxx>

class Geom_BSplineCurve;
class Geom_BSplineSurface;

#include <opencascade/gp_Ax1.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pnt3d;

	class Cad_RailRevolve
		: public Global_Done
	{

		/*Private Data*/

		Handle(Geom_BSplineCurve) theGeneratrix_;
		Handle(Geom_BSplineCurve) theRail_;

		gp_Ax1 theAx_;

		Standard_Real theTolerance_;

		Handle(Geom_BSplineSurface) thePatch_;

		//- private functions and operators


		//- static functions

	public:

		//- default constructor

		Cad_RailRevolve()
		{}

		//- constructors


		//- public functions and operators

		const auto& Generatrix() const
		{
			return theGeneratrix_;
		}

		const auto& Rail() const
		{
			return theRail_;
		}

		const auto& Axis() const
		{
			return theAx_;
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		const auto& Patch() const
		{
			return thePatch_;
		}

		TnbCad_EXPORT void Perform();

		void LoadGeneratrix(const Handle(Geom_BSplineCurve)& theCurve)
		{
			theGeneratrix_ = theCurve;
		}

		void LoadRail(const Handle(Geom_BSplineCurve)& theCurve)
		{
			theRail_ = theCurve;
		}

		void SetAxis(const gp_Ax1& theAx)
		{
			theAx_ = theAx;
		}

		void SetTolerance(const Standard_Real tol)
		{
			theTolerance_ = tol;
		}
	};
}

#endif // !_Cad_RailRevolve_Header
