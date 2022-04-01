#pragma once
#ifndef _GModel_ParaCurve_Header
#define _GModel_ParaCurve_Header

#include <Standard_Handle.hxx>
#include <GModel_Entity.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_BoxFwd.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	class GModel_ParaCurve
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<GModel_ParaCurve>
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theGeometry_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

		auto& ChangeGeometry()
		{
			return theGeometry_;
		}

		void CheckBoundary
		(
			const Standard_Real x,
			const char* theName
		) const;

		static TnbCad_EXPORT void CheckBounded
		(
			const Handle(Geom2d_Curve)& theCurve,
			const char* theName
		);


		//- default constructor

		GModel_ParaCurve()
		{}

	public:

		typedef Geom2d_Curve geomType;

		//- constructors

		TnbCad_EXPORT explicit GModel_ParaCurve
		(
			const Handle(Geom2d_Curve)& theGeometry
		);

		TnbCad_EXPORT GModel_ParaCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeometry
		);

		TnbCad_EXPORT GModel_ParaCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeometry
		);

		TnbCad_EXPORT GModel_ParaCurve
		(
			Handle(Geom2d_Curve)&& theGeometry
		);

		TnbCad_EXPORT GModel_ParaCurve
		(
			const Standard_Integer theIndex,
			Handle(Geom2d_Curve) && theGeometry
		);

		TnbCad_EXPORT GModel_ParaCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve)&& theGeometry
		);


		//- public functions and operators

		TnbCad_EXPORT Standard_Real FirstParameter() const;
		TnbCad_EXPORT Standard_Real LastParameter() const;

		TnbCad_EXPORT Pnt2d Value(const Standard_Real x) const;
		TnbCad_EXPORT Pnt2d Value_normParam(const Standard_Real x) const;

		TnbCad_EXPORT Pnt2d FirstCoord() const;
		TnbCad_EXPORT Pnt2d LastCoord() const;

		TnbCad_EXPORT Entity2d_Box CalcBoundingBox() const;

		const auto& Curve() const
		{
			return theGeometry_;
		}

		const auto& Geometry() const
		{
			return theGeometry_;
		}
	};
}

#include <GModel_ParaCurveI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::GModel_ParaCurve);

#endif // !_GModel_ParaCurve_Header
