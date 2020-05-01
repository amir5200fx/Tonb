#pragma once
#ifndef _HydStatic_hAuCurve_Header
#define _HydStatic_hAuCurve_Header

#include <HydStatic_AuCurve.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_GzQ;

	class HydStatic_hAuCurve
		: public HydStatic_AuCurve
	{

		/*Private Data*/

	public:

		HydStatic_hAuCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_hAuCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_hAuCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

		static std::shared_ptr<HydStatic_hAuCurve>
			AuCurve
			(
				const std::vector<HydStatic_GzQ>& theQs
			);
	};
}

#endif // !_HydStatic_hAuCurve_Header
