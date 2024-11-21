#pragma once
#ifndef _Pln_Curve_Header
#define _Pln_Curve_Header

#include <Cad2d_Module.hxx>
#include <Pln_Entity.hxx>
#include <Pnt2d.hxx>
#include <Vec2d.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Serialization.hxx>
#include <Global_AccessMethod.hxx>

class Geom2d_Curve;
class gp_Ax2d;
class gp_Ax22d;
class gp_Trsf2d;

#include <opencascade/Precision.hxx>

#include <memory>
#include <vector>
#include <tuple>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_IntsctEntity_TangSegment;

	class Pln_Curve
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Pln_Curve>
	{

		/*Private Data*/

		//- must be bounded
		Handle(Geom2d_Curve) theGeometry_;


		/*private functions and operators*/

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

		auto& ChangeGeometry()
		{
			return theGeometry_;
		}

		TnbCad2d_EXPORT void CheckBoundary(const Standard_Real x, const char* theName) const;

	public:

		typedef Pnt2d ptType;

		static TnbCad2d_EXPORT const std::string extension;

		//- default constructor

		Pln_Curve()
		{}


		//- constructors

		TnbCad2d_EXPORT Pln_Curve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbCad2d_EXPORT Pln_Curve
		(
			const Standard_Integer theIndex,
			Handle(Geom2d_Curve) && theGeom
		);

		TnbCad2d_EXPORT Pln_Curve
		(
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbCad2d_EXPORT Pln_Curve
		(
			Handle(Geom2d_Curve) && theGeom
		);

		TnbCad2d_EXPORT Pln_Curve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbCad2d_EXPORT Pln_Curve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve) && theGeom
		);


		//- public functions and operators

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		virtual inline Standard_Boolean IsGap() const;

		virtual TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			CreateCurve
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const Handle(Geom2d_Curve)&
			) const;

		TnbCad2d_EXPORT Standard_Boolean 
			IsRing
			(
				const Standard_Real tol = Precision::Confusion()
			) const;

		TnbCad2d_EXPORT Standard_Boolean IsLinear() const;

		TnbCad2d_EXPORT Standard_Real FirstParameter() const;
		TnbCad2d_EXPORT Standard_Real LastParameter() const;

		TnbCad2d_EXPORT Pnt2d Value(const Standard_Real x) const;
		TnbCad2d_EXPORT Pnt2d Value_normParam(const Standard_Real x) const;
		TnbCad2d_EXPORT std::tuple<Pnt2d, Vec2d> D1(const Standard_Real x) const;

		inline Pnt2d FirstCoord() const;
		inline Pnt2d LastCoord() const;

		TnbCad2d_EXPORT Entity2d_Box BoundingBox(const Standard_Real Tol) const;

		//Standard_Boolean IsOrphan() const override;

		TnbCad2d_EXPORT virtual std::shared_ptr<Pln_Curve> 
			operator()
			(
				const Handle(Geom2d_Curve)& theCurve
				) const;

		TnbCad2d_EXPORT virtual std::shared_ptr<Pln_Curve> 
			operator()
			(
				Handle(Geom2d_Curve)&& theCurve
				) const;

		TnbCad2d_EXPORT virtual std::shared_ptr<Pln_Curve>
			Copy() const;

		auto This() const
		{
			return std::const_pointer_cast<Pln_Curve>(this->shared_from_this());
		}

		//Pln_EntityType Type() const override;

		TnbCad2d_EXPORT void Reverse();

		TnbCad2d_EXPORT void Transform(const gp_Trsf2d& t);

		TnbCad2d_EXPORT void Interpolation
		(
			const std::vector<Pnt2d>& theQ,
			const Standard_Integer theDeg = 2,
			const Standard_Real theTol = 1.0E-6
		);

		TnbCad2d_EXPORT virtual std::tuple<std::shared_ptr<Pln_Curve>, std::shared_ptr<Pln_Curve>>
			Split(const Standard_Real x) const;

		TnbCad2d_EXPORT virtual void Split
		(
			const Standard_Real x,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const;

		TnbCad2d_EXPORT virtual void Split
		(
			const Standard_Real x,
			Pnt2d& theCoord,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const;

		TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Curve>> Split
		(
			const std::vector<Standard_Real>& theParameters
		) const;

		TnbCad2d_EXPORT void Split
		(
			const std::vector<Standard_Real>& theParameters,
			std::vector<Pnt2d>& theCoords,
			std::vector<std::shared_ptr<Pln_Curve>>& theCurves
		) const;

		TnbCad2d_EXPORT virtual std::tuple
			<
			std::shared_ptr<Pln_Curve>,
			std::shared_ptr<Pln_Curve>,
			std::shared_ptr<Pln_Curve>
			>
			Split
			(
				const Cad2d_IntsctEntity_TangSegment& x
			) const;

		virtual Standard_Boolean IsTangential() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsMarine() const
		{
			return Standard_False;
		}

		// Static functions and operators

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			Clip
			(
				const Pln_Curve& theCurve,
				const Standard_Real theP0,
				const Standard_Real theP1
			)
		{
			NotImplemented;
			return nullptr;
		}

		static TnbCad2d_EXPORT std::shared_ptr<Entity2d_Polygon>
			Discretize
			(
				const Pln_Curve& theCurve,
				const Standard_Integer theNbSegments
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			MakeLineSegment
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			MakeCircularArc
			(
				const gp_Ax22d& A,
				const Standard_Real Radius,
				const Standard_Real theDeg0,
				const Standard_Real theDeg1
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			MakeCircularArc
			(
				const gp_Ax2d& A,
				const Standard_Real Radius,
				const Standard_Real theDeg0,
				const Standard_Real theDeg1,
				const Standard_Boolean Sense = Standard_True
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			MakeEllipse
			(
				const gp_Ax2d& MajorAxis,
				const Standard_Real MajorRadius,
				const Standard_Real MinorRadius,
				const Standard_Boolean Sense = Standard_True
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			MakeEllipse
			(
				const gp_Ax22d& Axis,
				const Standard_Real MajorRadius,
				const Standard_Real MinorRadius
			);

		static TnbCad2d_EXPORT Standard_Boolean 
			IsValid
			(
				const std::shared_ptr<Pln_Curve>& theCurve, 
				const Standard_Real theTol
			);

		static TnbCad2d_EXPORT Standard_Boolean 
			IsDegenerate
			(
				const std::shared_ptr<Pln_Curve>& theCurve, 
				const Standard_Real theTol
			);
		//- Macros


	};
}

#include <Pln_CurveI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::Pln_Curve);

#endif // !_Pln_Curve_Header 
