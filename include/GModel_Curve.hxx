#pragma once
#ifndef _GModel_Curve_Header
#define _GModel_Curve_Header

#include <Standard_Handle.hxx>
#include <GModel_Entity.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Cad_Module.hxx>

class Geom_Curve;

namespace tnbLib
{

	class GModel_Curve
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


		//- default constructor

		GModel_Curve()
		{}

	public:


		//- constructors

		TnbCad_EXPORT GModel_Curve
		(
			const Handle(Geom_Curve)& theGeometry
		);

		TnbCad_EXPORT GModel_Curve
		(
			Handle(Geom_Curve)&& theGeometry
		);


		//- public functions and operators

		TnbCad_EXPORT Standard_Real FirstParameter() const;
		TnbCad_EXPORT Standard_Real LastParameter() const;

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

#include <GModel_CurveI.hxx>

#endif // !_GModel_Curve_Header
