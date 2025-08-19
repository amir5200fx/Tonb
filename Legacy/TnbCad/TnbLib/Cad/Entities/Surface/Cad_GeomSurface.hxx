#pragma once
#ifndef _Cad_GeomSurface_Header
#define _Cad_GeomSurface_Header

#include <Global_Serialization.hxx>
#include <Global_Named.hxx>
#include <Global_Indexed.hxx>
#include <Global_Handle.hxx>
#include <Cad_Module.hxx>
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>

class Geom_Surface;

#include <memory>

namespace tnbLib
{

	class Cad_GeomSurface
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		Handle(Geom_Surface) theSurface_;


		/*Private functions and operators*/

		TNB_SERIALIZATION(TnbCad_EXPORT);


		// default constructor

		Cad_GeomSurface()
		{}


		static TnbCad_EXPORT void CheckBounded(const Handle(Geom_Surface)&);

	public:


		static TnbCad_EXPORT const std::string extension;

		//- constructors

		TnbCad_EXPORT Cad_GeomSurface
		(
			const Handle(Geom_Surface)& theSurface
		);

		TnbCad_EXPORT Cad_GeomSurface
		(
			Handle(Geom_Surface)&& theSurface
		);

		TnbCad_EXPORT Cad_GeomSurface
		(
			const Standard_Integer theIndex, 
			const Handle(Geom_Surface)& theSurface
		);

		TnbCad_EXPORT Cad_GeomSurface
		(
			const Standard_Integer theIndex, 
			Handle(Geom_Surface)&& theSurface
		);

		TnbCad_EXPORT Cad_GeomSurface
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Handle(Geom_Surface)& theSurface
		);

		TnbCad_EXPORT Cad_GeomSurface
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			Handle(Geom_Surface)&& theSurface
		);


		//- public functions and operators

		const auto& Geometry() const
		{
			return theSurface_;
		}

		TnbCad_EXPORT Standard_Real FirstParameterU() const;
		TnbCad_EXPORT Standard_Real LastParameterU() const;

		TnbCad_EXPORT Standard_Real FirstParameterV() const;
		TnbCad_EXPORT Standard_Real LastParameterV() const;

		TnbCad_EXPORT Pnt3d Value(const Standard_Real u, const Standard_Real v) const;
		TnbCad_EXPORT Pnt3d Value(const Pnt2d&) const;

		TnbCad_EXPORT Entity2d_Box ParametricBoundingBox() const;
		TnbCad_EXPORT Entity3d_Box BoundingBox() const;
	};
}

#endif // !_Cad_GeomSurface_Header
