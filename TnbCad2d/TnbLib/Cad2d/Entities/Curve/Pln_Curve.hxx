#pragma once
#ifndef _Pln_Curve_Header
#define _Pln_Curve_Header

#include <Standard_Handle.hxx>
#include <Global_AccessMethod.hxx>
#include <Pln_Entity.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>

class Geom2d_Curve;
class gp_Ax2d;
class gp_Ax22d;

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve_Info;

	class Pln_Curve
		: public Pln_Entity
	{

		typedef Pln_Curve_Info info;

		/*Private Data*/

		//- must be bounded
		Handle(Geom2d_Curve) theGeometry_;

		std::shared_ptr<info> theInfo_;


		Handle(Geom2d_Curve)& ChangeGeometry()
		{
			return theGeometry_;
		}

		void CheckBoundary(const Standard_Real x, const char* theName) const;

	public:

		Pln_Curve(const std::shared_ptr<info>& theInfo)
			: theInfo_(theInfo)
		{}

		Pln_Curve
		(
			const Handle(Geom2d_Curve)& theGeom,
			const std::shared_ptr<info>& theInfo
		);

		Pln_Curve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom,
			const std::shared_ptr<info>& theInfo
		);

		const Handle(Geom2d_Curve)& Geometry() const
		{
			return theGeometry_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		Standard_Real FirstParameter() const;

		Standard_Real LastParameter() const;

		Pnt2d Value(const Standard_Real x) const;

		Pnt2d Value_normParam(const Standard_Real x) const;

		Pnt2d FirstCoord() const;

		Pnt2d LastCoord() const;

		Entity2d_Box CalcBoundingBox() const;

		void Interpolation
		(
			const std::vector<Pnt2d>& theQ,
			const Standard_Integer theDeg = 2, 
			const Standard_Real theTol = 1.0E-6
		);

		void Split
		(
			const Standard_Real x,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const;

		void Split
		(
			const Standard_Real x,
			Pnt2d& theCoord,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const;


		// Static functions and operators

		static std::shared_ptr<Entity2d_Polygon>
			Discretize
			(
				const Pln_Curve& theCurve,
				const Standard_Integer theNbSegments
			);

		static std::shared_ptr<Pln_Curve>
			MakeLineSegment
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const std::shared_ptr<info>& theInfo
			);

		static std::shared_ptr<Pln_Curve>
			MakeCircularArc
			(
				const gp_Ax22d& A,
				const Standard_Real Radius,
				const Standard_Real theDeg0,
				const Standard_Real theDeg1,
				const std::shared_ptr<info>& theInfo
			);

		static std::shared_ptr<Pln_Curve>
			MakeCircularArc
			(
				const gp_Ax2d& A,
				const Standard_Real Radius,
				const Standard_Real theDeg0,
				const Standard_Real theDeg1,
				const std::shared_ptr<info>& theInfo,
				const Standard_Boolean Sense = Standard_True
			);

		static std::shared_ptr<Pln_Curve> 
			MakeEllipse
			(
				const gp_Ax2d& MajorAxis,
				const Standard_Real MajorRadius,
				const Standard_Real MinorRadius,
				const std::shared_ptr<info>& theInfo, 
				const Standard_Boolean Sense = Standard_True
			);

		static std::shared_ptr<Pln_Curve> 
			MakeEllipse
			(
				const gp_Ax22d& Axis,
				const Standard_Real MajorRadius,
				const Standard_Real MinorRadius,
				const std::shared_ptr<info>& theInfo
			);

		//- Macros


	};
}

#include <Pln_CurveI.hxx>

#endif // !_Pln_Curve_Header
