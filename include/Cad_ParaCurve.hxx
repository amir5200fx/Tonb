#pragma once
#ifndef _Cad_ParaCurve_Header
#define _Cad_ParaCurve_Header

#include <Cad_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

class Geom2d_Curve;

#include <Standard_Handle.hxx>

namespace tnbLib
{

	class Cad_ParaCurve
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theGeometry_;

		// private functions and operators [5/12/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

		TnbCad_EXPORT void CheckBoundary
		(
			const Standard_Real x,
			const char* theName
		) const;

		static TnbCad_EXPORT void CheckBounded
		(
			const Handle(Geom2d_Curve)& theCurve,
			const char* theName
		);

	protected:

		// default constructor [5/12/2022 Amir]

		Cad_ParaCurve()
		{}


		// constructors [5/12/2022 Amir]

		TnbCad_EXPORT explicit Cad_ParaCurve
		(
			const Handle(Geom2d_Curve)& theGeometry
		);

		TnbCad_EXPORT Cad_ParaCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeometry
		);

		TnbCad_EXPORT Cad_ParaCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeometry
		);

		TnbCad_EXPORT Cad_ParaCurve
		(
			Handle(Geom2d_Curve) && theGeometry
		);

		TnbCad_EXPORT Cad_ParaCurve
		(
			const Standard_Integer theIndex,
			Handle(Geom2d_Curve) && theGeometry
		);

		TnbCad_EXPORT Cad_ParaCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve) && theGeometry
		);


	public:

		// virtual functions [5/12/2022 Amir]

		virtual Standard_Boolean IsGap() const
		{
			return Standard_False;
		}

		// public functions and operators [5/12/2022 Amir]

		TnbCad_EXPORT Standard_Real FirstParameter() const;
		TnbCad_EXPORT Standard_Real LastParameter() const;

		TnbCad_EXPORT Pnt2d Value(const Standard_Real x) const;
		TnbCad_EXPORT Pnt2d Value_normParam(const Standard_Real x) const;

		inline Pnt2d FirstCoord() const;
		inline Pnt2d LastCoord() const;

		TnbCad_EXPORT Entity2d_Box CalcBoundingBox() const;

		const auto& Curve() const
		{
			return theGeometry_;
		}

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		TnbCad_EXPORT void Reverse();
	};
}

#include <Cad_ParaCurveI.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Cad_ParaCurve);

#endif // !_Cad_ParaCurve_Header
