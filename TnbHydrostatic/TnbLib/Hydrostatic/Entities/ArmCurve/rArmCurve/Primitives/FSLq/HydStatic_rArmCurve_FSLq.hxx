#pragma once
#ifndef _HydStatic_rArmCurve_FSLq_Header
#define _HydStatic_rArmCurve_FSLq_Header

#include <HydStatic_rArmCurve_Prim.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class rArmCurve_FSLq
			: public rArmCurve_Prim
		{

			/*Private Data*/

		protected:

			rArmCurve_FSLq
			(
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theCurve)
			{}

			rArmCurve_FSLq
			(
				const Standard_Integer theIndex, 
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theIndex, theCurve)
			{}

			rArmCurve_FSLq
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

#endif // !_HydStatic_rArmCurve_FSLq_Header
