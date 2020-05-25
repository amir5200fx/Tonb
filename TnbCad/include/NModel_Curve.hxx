#pragma once
#ifndef _NModel_Curve_Header
#define _NModel_Curve_Header

#include <NModel_Entity.hxx>
#include <Entity3d_BoxFwd.hxx>

#include <Standard_Handle.hxx>

class Geom_Curve;

namespace tnbLib
{

	class NModel_Curve
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<NModel_Curve>
	{

		/*Private Data*/

		Handle(Geom_Curve) theGeometry_;


		auto& ChangeGeometry()
		{
			return theGeometry_;
		}

		void CheckBoundary
		(
			const Standard_Real x,
			const char* theName
		) const;

		static void CheckBounded
		(
			const Handle(Geom_Curve)& theCurve,
			const char* theName
		);

	public:

		NModel_Curve
		(
			const Handle(Geom_Curve)& theGeometry
		);

		NModel_Curve
		(
			const Standard_Integer theIndex,
			const Handle(Geom_Curve)& theGeometry
		);

		NModel_Curve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_Curve)& theGeometry
		);

		Standard_Real FirstParameter() const;

		Standard_Real LastParameter() const;

		Pnt3d Value(const Standard_Real x) const;

		Pnt3d Value_normParam(const Standard_Real x) const;

		Pnt3d FirstCoord() const;

		Pnt3d LastCoord() const;

		Entity3d_Box CalcBoundingBox() const;

		const auto& Geometry() const
		{
			return theGeometry_;
		}
	};
}

#include <NModel_CurveI.hxx>

#endif // !_NModel_Curve_Header
