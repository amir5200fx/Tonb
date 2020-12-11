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

		TnbHydStatic_EXPORT HydStatic_hAuCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_hAuCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_hAuCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_hAuCurve>
			AuCurve
			(
				const std::vector<HydStatic_GzQ>& theQs
			);
	};
}

#endif // !_HydStatic_hAuCurve_Header
