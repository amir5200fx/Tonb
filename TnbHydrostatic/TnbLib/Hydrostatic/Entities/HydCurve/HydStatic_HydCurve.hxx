#pragma once
#ifndef _HydStatic_HydCurve_Header
#define _HydStatic_HydCurve_Header

#include <HydStatic_Entity.hxx>
#include <Standard_Handle.hxx>

class Geom2d_Curve;


namespace tnbLib
{

	class HydStatic_HydCurve
		: public HydStatic_Entity
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theGeom_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	protected:

		//- default constructor

		HydStatic_HydCurve()
		{}


		//- constructors

		TnbHydStatic_EXPORT HydStatic_HydCurve
		(
			Handle(Geom2d_Curve)&& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_HydCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_HydCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve)&& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_HydCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	public:


		//- public functions and operators


		const auto& Geometry() const
		{
			return theGeom_;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_HydCurve);

#endif // !_HydStatic_HydCurve_Header
