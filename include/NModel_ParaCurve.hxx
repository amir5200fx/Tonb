#pragma once
#ifndef _NModel_ParaCurve_Header
#define _NModel_ParaCurve_Header

#include <NModel_Entity.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <OFstream.hxx>

#include <Standard_Handle.hxx>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	class NModel_ParaCurve
		: public NModel_Entity
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theGeometry_;

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
			const Handle(Geom2d_Curve)& theCurve,
			const char* theName
		);

	public:

		TnbCad_EXPORT NModel_ParaCurve
		(
			const Handle(Geom2d_Curve)& theGeometry
		);

		TnbCad_EXPORT Standard_Real FirstParameter() const;

		TnbCad_EXPORT Standard_Real LastParameter() const;

		TnbCad_EXPORT Pnt2d Value(const Standard_Real x) const;

		TnbCad_EXPORT Pnt2d Value_normParam(const Standard_Real x) const;

		Pnt2d FirstCoord() const;

		Pnt2d LastCoord() const;

		TnbCad_EXPORT Entity2d_Box CalcBoundingBox() const;

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		//- IO functions and operators

		//void ExportToPlt(OFstream& File) const;
	};
}

#include <NModel_ParaCurveI.hxx>

#endif // !_NModel_ParaCurve_Header
