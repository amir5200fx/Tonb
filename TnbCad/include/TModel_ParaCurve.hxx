#pragma once
#ifndef _TModel_ParaCurve_Header
#define _TModel_ParaCurve_Header

#include <TModel_Entity.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <OFstream.hxx>

#include <Standard_Handle.hxx>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	class TModel_ParaCurve
		: public TModel_Entity
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theGeometry_;


		//- private functions and operators

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
			const Handle(Geom2d_Curve)& theCurve,
			const char* theName
		);


		TNB_SERIALIZATION(TnbCad_EXPORT);


	protected:


		//- default constructor

		TModel_ParaCurve()
		{}

	public:

		// constructors [1/5/2022 Amir]

		TnbCad_EXPORT explicit TModel_ParaCurve
		(
			const Handle(Geom2d_Curve)& theGeometry
		);


		// public functions and operators [1/5/2022 Amir]

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

#include <TModel_ParaCurveI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_ParaCurve);

#endif // !_TModel_ParaCurve_Header
