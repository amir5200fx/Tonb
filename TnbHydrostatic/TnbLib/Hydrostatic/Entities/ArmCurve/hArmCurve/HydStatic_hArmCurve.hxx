#pragma once
#ifndef _HydStatic_hArmCurve_Header
#define _HydStatic_hArmCurve_Header

#include <HydStatic_ArmCurve.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_hAuCurve;
	class HydStatic_CmptLib;

	class HydStatic_hArmCurve
		: public HydStatic_ArmCurve
	{

		friend class HydStatic_CmptLib;

		/*Private Data*/

		std::shared_ptr<HydStatic_hAuCurve> theAuCurve_;


		auto& ChangeAuCurve()
		{
			return theAuCurve_;
		}

	public:

		HydStatic_hArmCurve
		(
			const Handle(Geom2d_Curve)&& theCurve
		);

		HydStatic_hArmCurve
		(
			const Handle(Geom2d_Curve) & theCurve
		);

		HydStatic_hArmCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_hArmCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

		Standard_Boolean HasAuCurve() const
		{
			return (Standard_Boolean)theAuCurve_;
		}
		
		const auto& AuCurve() const
		{
			return theAuCurve_;
		}

		void SetAuCurve
		(
			const std::shared_ptr<HydStatic_hAuCurve>&& theCurve
		)
		{
			theAuCurve_ = std::move(theCurve);
		}
		
	};
}

#endif // !_HydStatic_hArmCurve_Header
