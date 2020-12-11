#pragma once
#ifndef _HydStatic_rArmCurve_LDT_Header
#define _HydStatic_rArmCurve_LDT_Header

#include <HydStatic_rArmCurve_Prim.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class rArmCurve_LDT
			: public rArmCurve_Prim
		{

			/*Private Data*/

			Standard_Real theD_;

		protected:

			rArmCurve_LDT
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theD
			)
				: rArmCurve_Prim(theCurve)
				, theD_(theD)
			{}

			rArmCurve_LDT
			(
				const Standard_Integer theIndex, 
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theD
			)
				: rArmCurve_Prim(theIndex, theCurve)
				, theD_(theD)
			{}

			rArmCurve_LDT
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theD
			)
				: rArmCurve_Prim(theIndex, theName, theCurve)
				, theD_(theD)
			{}

		public:

			auto D() const
			{
				return theD_;
			}

			std::shared_ptr<HydStatic_rArmCurve> ExpandToPort() const override
			{
				NotImplemented;
				return nullptr;
			}
		};
	}
}

#endif // !_HydStatic_rArmCurve_LDT_Header
