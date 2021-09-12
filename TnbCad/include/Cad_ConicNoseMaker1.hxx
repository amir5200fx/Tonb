#pragma once
#ifndef _Cad_ConicNoseMaker_Header
#define _Cad_ConicNoseMaker_Header

#include <Global_Done.hxx>
#include <Cad_Module.hxx>

class Geom_BSplineSurface;
class Geom_Surface;

#include <Standard_Handle.hxx>
#include <gp_Ax1.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pnt3d;
	class Cad_PolesNetPrcssr;

	class Cad_ConicNoseMaker
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

		enum class entityType
		{
			point,
			line,
			plane
		};

	private:

		/*Private Data*/

		bndPatch theBoundary_;

		gp_Ax1 theAxis_;
		Standard_Real theParameter_;
		Standard_Real theWeight_;

		Handle(Geom_BSplineSurface) theSurface_;

		Handle(Geom_Surface) theNose_;

		//std::vector<Standard_Real> theMaxAngles_;

	public:

		//- default constructor

		Cad_ConicNoseMaker()
			: theParameter_(0)
			, theWeight_(1.0)
		{}


		//- constructors

		Cad_ConicNoseMaker(const Handle(Geom_BSplineSurface)& theSurface)
			: theSurface_(theSurface)
			, theParameter_(0.0)
			, theWeight_(1.0)
		{}


		//- public functions and operators

		auto Boundary() const
		{
			return theBoundary_;
		}

		auto Parameter() const
		{
			return theParameter_;
		}

		auto Weight() const
		{
			return theWeight_;
		}

		const auto& Axis() const
		{
			return theAxis_;
		}

		const auto& Surface() const
		{
			return theSurface_;
		}

		const auto& Nose() const
		{
			return theNose_;
		}

		void Perform();

		void LoadSurface(const Handle(Geom_BSplineSurface)& theSurface)
		{
			theSurface_ = theSurface;
		}

		void SetParameter(const Standard_Real x)
		{
			theParameter_ = x;
		}

		void SetWeight(const Standard_Real x)
		{
			theWeight_ = x;
		}

		void SetAxis(const gp_Ax1& theAx)
		{
			theAxis_ = theAx;
		}


		//- static functions and operators

		static std::vector<std::pair<Pnt3d, Pnt3d>> RetrieveBoundaryPoles(const bndPatch, const std::shared_ptr<Cad_PolesNetPrcssr>&);
	};
}

#endif // !_Cad_ConicNoseMaker_Header
