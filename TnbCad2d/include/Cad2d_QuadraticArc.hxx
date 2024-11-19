#pragma once
#ifndef _Cad2d_QuadraticArc_Header
#define _Cad2d_QuadraticArc_Header

#include <Cad2d_Module.hxx>
#include <Global_Done.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>

#include <Global_Handle.hxx>

class Geom2d_BSplineCurve;

namespace tnbLib
{

	// FOrward Declarations


	class Cad2d_QuadraticArc
		: public Global_Done
	{

		/*Private Data*/

		Pnt2d theP0_;
		Pnt2d theP2_;

		Pnt2d thePtOnCrv_;

		Dir2d theDir0_;
		Dir2d theDir2_;

		Standard_Real theTolerance_;

		Handle(Geom2d_BSplineCurve) theGeom_;

	public:

		//- default constructor

		Cad2d_QuadraticArc()
			: theTolerance_(1.0E-6)
		{}


		//- constructors

		Cad2d_QuadraticArc
		(
			const Pnt2d& theP0, 
			const Dir2d& theDir0, 
			const Pnt2d& theP2, 
			const Dir2d& theDir2,
			const Pnt2d& thePtOnCrv
		)
			: theP0_(theP0)
			, theP2_(theP2)
			, theDir0_(theDir0)
			, theDir2_(theDir2)
			, thePtOnCrv_(thePtOnCrv)
			, theTolerance_(1.0E-6)
		{}

		//- public functions and operators

		auto Tolerance() const
		{
			return theTolerance_;
		}

		const auto& P0() const
		{
			return theP0_;
		}

		const auto& P2() const
		{
			return theP2_;
		}

		const auto& Dir0() const
		{
			return theDir0_;
		}

		const auto& Dir2() const
		{
			return theDir2_;
		}

		const auto& PtOnCrv() const
		{
			return thePtOnCrv_;
		}

		const auto& Geometry() const
		{
			return theGeom_;
		}

		TnbCad2d_EXPORT void Perform();

		void SetTolerance(const Standard_Real x)
		{
			theTolerance_ = x;
		}

		void SetP0(const Pnt2d& theP)
		{
			theP0_ = theP;
		}

		void SetP0(Pnt2d&& theP)
		{
			theP0_ = std::move(theP);
		}

		void SetP2(const Pnt2d& theP)
		{
			theP2_ = theP;
		}

		void SetP2(Pnt2d&& theP)
		{
			theP2_ = std::move(theP);
		}

		void SetDir0(const Dir2d& theDir)
		{
			theDir0_ = theDir;
		}

		void SetDir0(Dir2d&& theDir)
		{
			theDir0_ = std::move(theDir);
		}

		void SetDir2(const Dir2d& theDir)
		{
			theDir2_ = theDir;
		}

		void SetDir2(Dir2d&& theDir)
		{
			theDir2_ = std::move(theDir);
		}

		void SetPtOnCrv(const Pnt2d& thePt)
		{
			thePtOnCrv_ = thePt;
		}

		void SetPtOnCrv(Pnt2d&& theP)
		{
			thePtOnCrv_ = std::move(theP);
		}
	};
}

#endif // !_Cad2d_QuadraticArc_Header
