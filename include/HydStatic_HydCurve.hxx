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

	protected:

		HydStatic_HydCurve
		(
			const Handle(Geom2d_Curve)&& theCurve
		);

		HydStatic_HydCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_HydCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_HydCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	public:


		const auto& Geometry() const
		{
			return theGeom_;
		}
	};
}

#endif // !_HydStatic_HydCurve_Header
