#pragma once
#ifndef _HydStatic_rArmCurve_Body_Header
#define _HydStatic_rArmCurve_Body_Header

#include <HydStatic_rArmCurve_Prim.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class rArmCurve_Body
			: public rArmCurve_Prim
		{

			/*Private Data*/

		protected:

			rArmCurve_Body
			(
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theCurve)
			{}

			/*rArmCurve_Body
			(
				const Standard_Integer theIndex,
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theIndex, theCurve)
			{}*/

			rArmCurve_Body
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theIndex, theName, theCurve)
			{}

		public:

			std::shared_ptr<HydStatic_rArmCurve>
				ExpandToPort() const override
			{
				NotImplemented;
				return nullptr;
			}
		};
	}
}

#endif // !_HydStatic_rArmCurve_Body_Header
