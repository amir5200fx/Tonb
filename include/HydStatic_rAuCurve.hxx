#pragma once
#ifndef _HydStatic_rAuCurve_Header
#define _HydStatic_rAuCurve_Header

#include <HydStatic_AuCurve.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_GzQ;

	class HydStatic_rAuCurve
		: public HydStatic_AuCurve
	{

		/*Private Data*/

	public:


		HydStatic_rAuCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_rAuCurve
		(
			const Handle(Geom2d_Curve)&& theCurve
		);

		HydStatic_rAuCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_rAuCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);



		static std::shared_ptr<HydStatic_rAuCurve>
			AuCurve
			(
				const std::vector<HydStatic_GzQ>& theQs
			);

	};
}

#endif // !_HydStatic_rAuCurve_Header
