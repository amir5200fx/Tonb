#pragma once
#ifndef _HydStatic_rArmCurve_Prim_Header
#define _HydStatic_rArmCurve_Prim_Header

#include <HydStatic_rArmCurve.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class rArmCurve_Prim
			: public HydStatic_rArmCurve
		{

			/*Private Data*/

		protected:

			rArmCurve_Prim
			(
				const Handle(Geom2d_Curve)& theCurve
			)
				: HydStatic_rArmCurve(theCurve)
			{}

			rArmCurve_Prim
			(
				const Standard_Integer theIndex,
				const Handle(Geom2d_Curve)& theCurve
			)
				: HydStatic_rArmCurve(theIndex, theCurve)
			{}

			rArmCurve_Prim
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Handle(Geom2d_Curve)& theCurve
			)
				: HydStatic_rArmCurve(theIndex, theName, theCurve)
			{}

		public:

			Standard_Boolean IsPrim() const override
			{
				return Standard_True;
			}

		};
	}
}

#endif // !_HydStatic_rArmCurve_Prim_Header
