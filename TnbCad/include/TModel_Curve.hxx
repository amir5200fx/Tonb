#pragma once
#ifndef _TModel_Curve_Header
#define _TModel_Curve_Header

#include <TModel_Entity.hxx>
#include <Entity3d_BoxFwd.hxx>

#include <Standard_Handle.hxx>

class Geom_Curve;

namespace tnbLib
{

	class TModel_Curve
		: public TModel_Entity
	{

		/*Private Data*/

		Handle(Geom_Curve) theGeometry_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


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


	protected:

		//- default constructor for serialization purposes only!

		TModel_Curve()
		{}

	public:

		TnbCad_EXPORT TModel_Curve
		(
			const Handle(Geom_Curve) theGeometry
		);


		//- public functions and operators

		TnbCad_EXPORT Standard_Real FirstParameter() const;

		TnbCad_EXPORT Standard_Real LastParameter() const;

		TnbCad_EXPORT Pnt3d Value(const Standard_Real x) const;

		TnbCad_EXPORT Pnt3d Value_normParam(const Standard_Real x) const;

		Pnt3d FirstCoord() const;

		Pnt3d LastCoord() const;

		TnbCad_EXPORT Entity3d_Box CalcBoundingBox() const;

		const auto& Geometry() const
		{
			return theGeometry_;
		}
	};
}

#include <TModel_CurveI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_Curve);

#endif // !_TModel_Curve_Header
