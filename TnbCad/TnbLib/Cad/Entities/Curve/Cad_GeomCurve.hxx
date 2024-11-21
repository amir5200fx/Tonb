#pragma once
#ifndef _Cad_GeomCurve_Header
#define _Cad_GeomCurve_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Serialization.hxx>
#include <Global_Handle.hxx>
#include <Cad_Module.hxx>
#include <Entity3d_BoxFwd.hxx>


class Geom_Curve;

namespace tnbLib
{

	//- Forward Declarations
	class Pnt3d;

	class Cad_GeomCurve
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		Handle(Geom_Curve) theGeometry_;


		/*Private functions and operators*/

		TNB_SERIALIZATION(TnbCad_EXPORT);

		//- default constructor

		Cad_GeomCurve()
		{}

		static TnbCad_EXPORT void CheckBounded(const Handle(Geom_Curve)&);

	public:

		static TnbCad_EXPORT const std::string extension;

		//- constructors

		TnbCad_EXPORT Cad_GeomCurve(const Handle(Geom_Curve)&);

		TnbCad_EXPORT Cad_GeomCurve(Handle(Geom_Curve) && );

		TnbCad_EXPORT Cad_GeomCurve(const Standard_Integer theIndex, const Handle(Geom_Curve)&);
		TnbCad_EXPORT Cad_GeomCurve(const Standard_Integer theIndex, Handle(Geom_Curve) && );

		TnbCad_EXPORT Cad_GeomCurve(const Standard_Integer theIndex, const word& theName, const Handle(Geom_Curve)&);
		TnbCad_EXPORT Cad_GeomCurve(const Standard_Integer theIndex, const word& theName, Handle(Geom_Curve) && );


		//- public functions and operators

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		TnbCad_EXPORT Standard_Real FirstParameter() const;
		TnbCad_EXPORT Standard_Real LastParameter() const;

		TnbCad_EXPORT Pnt3d FirstValue() const;
		TnbCad_EXPORT Pnt3d LastValue() const;

		TnbCad_EXPORT Pnt3d Value(const Standard_Real x) const;

		TnbCad_EXPORT Entity3d_Box CalcBoundingBox() const;
	};
}

#endif // !_Cad_GeomCurve_Header
