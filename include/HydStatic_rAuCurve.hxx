#pragma once
#ifndef _HydStatic_rAuCurve_Header
#define _HydStatic_rAuCurve_Header

#include <HydStatic_AuCurve.hxx>

namespace tnbLib
{

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
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_rAuCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	};
}

#endif // !_HydStatic_rAuCurve_Header
