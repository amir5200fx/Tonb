#pragma once
#ifndef _HydStatic_rArmCurve_Header
#define _HydStatic_rArmCurve_Header

#include <HydStatic_ArmCurve.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_rAuCurve;
	class HydStatic_CmptLib;

	class HydStatic_rArmCurve
		: public HydStatic_ArmCurve
	{

		friend class HydStatic_CmptLib;

		/*Private Data*/

		std::shared_ptr<HydStatic_rAuCurve> theAuCurve_;


		auto& ChangeAuCurve()
		{
			return theAuCurve_;
		}

	public:

		HydStatic_rArmCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_rArmCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_rArmCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);


		const auto& AuCurve() const
		{
			return theAuCurve_;
		}

	};
}

#endif // !_HydStatic_rArmCurve_Header
