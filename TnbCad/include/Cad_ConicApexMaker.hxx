#pragma once
#ifndef _Cad_ConicApexMaker_Header
#define _Cad_ConicApexMaker_Header

#include <Global_Done.hxx>
#include <Cad_Module.hxx>
#include <Pnt3d.hxx>
#include <Dir3d.hxx>

class Geom_BSplineSurface;
class Geom_Surface;

#include <Standard_Handle.hxx>
#include <gp_Ax1.hxx>

#include <vector>

namespace tnbLib
{

	class Cad_ConicApexMaker
		: public Global_Done
	{

	public:

		enum class bndPatch
		{
			U0,
			Un,
			V0,
			Vn
		};

		typedef std::pair<Pnt3d, Standard_Real> Pw;

	private:

		/*Private Data*/


		bndPatch theBoundary_;

		gp_Ax1 theAxis_;

		Handle(Geom_BSplineSurface) theSurface_;

		Handle(Geom_Surface) theApex_;

		Standard_Real theTolerance_;


		//- private functions and operators

		TnbCad_EXPORT std::pair<std::vector<Pw>, std::vector<Pw>> RetrieveBoundary() const;
		TnbCad_EXPORT std::vector<std::pair<Standard_Real, Standard_Integer>> RetrieveBoundaryKnots() const;

		TnbCad_EXPORT Standard_Integer RetrieveBoundaryDegree() const;

		TnbCad_EXPORT Pnt3d RetrieveOrigin() const;

	public:

		//- default constructor

		Cad_ConicApexMaker()
		{}


		//- constructors

		Cad_ConicApexMaker(const Handle(Geom_BSplineSurface)& theSurface)
			: theSurface_(theSurface)
		{}


		//- public functions and operators

		auto Boundary() const
		{
			return theBoundary_;
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		const auto& Axis() const
		{
			return theAxis_;
		}

		const auto& Surface() const
		{
			return theSurface_;
		}

		const auto& Apex() const
		{
			return theApex_;
		}

		TnbCad_EXPORT void Perform();

		void LoadSurface(const Handle(Geom_BSplineSurface)& theSurface)
		{
			theSurface_ = theSurface;
		}

		void SetAxis(const gp_Ax1& theAx)
		{
			theAxis_ = theAx;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}
	};
}

#endif // !_Cad_ConicApexMaker_Header
