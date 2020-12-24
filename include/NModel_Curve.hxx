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

		TnbCad_EXPORT void CheckBoundary
		(
			const Standard_Real x,
			const char* theName
		) const;

		static TnbCad_EXPORT void CheckBounded
		(
			const Handle(Geom_Curve)& theCurve,
			const char* theName
		);

	public:

		TnbCad_EXPORT NModel_Curve
		(
			const Handle(Geom_Curve)& theGeometry
		);

		TnbCad_EXPORT NModel_Curve
		(
			const Standard_Integer theIndex,
			const Handle(Geom_Curve)& theGeometry
		);

		TnbCad_EXPORT NModel_Curve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_Curve)& theGeometry
		);

		Standard_Real FirstParameter() const;

		Standard_Real LastParameter() const;

		TnbCad_EXPORT Pnt3d Value(const Standard_Real x) const;

		TnbCad_EXPORT Pnt3d Value_normParam(const Standard_Real x) const;

		TnbCad_EXPORT Pnt3d FirstCoord() const;

		TnbCad_EXPORT Pnt3d LastCoord() const;

		TnbCad_EXPORT Entity3d_Box CalcBoundingBox() const;

		const auto& Geometry() const
		{
			return theGeometry_;
		}
	};
}

#include <NModel_CurveI.hxx>

#endif // !_NModel_Curve_Header
