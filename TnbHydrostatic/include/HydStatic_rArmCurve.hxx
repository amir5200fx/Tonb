#pragma once
#ifndef _HydStatic_rArmCurve_Header
#define _HydStatic_rArmCurve_Header

#include <HydStatic_ArmCurve.hxx>

namespace tnbLib
{

	class HydStatic_rArmCurve
		: public HydStatic_ArmCurve
	{

		friend class HydStatic_CmptLib;

		/*Private Data*/

	protected:

		TnbHydStatic_EXPORT HydStatic_rArmCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_rArmCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_rArmCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	public:

		
		virtual Standard_Boolean IsEffective() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsPrim() const
		{
			return Standard_False;
		}

		virtual std::shared_ptr<HydStatic_rArmCurve>
			ExpandToPort() const = 0;

	};
}

#endif // !_HydStatic_rArmCurve_Header
