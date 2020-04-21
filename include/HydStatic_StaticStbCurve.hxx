#pragma once
#ifndef _HydStatic_StaticStbCurve_Header
#define _HydStatic_StaticStbCurve_Header

#include <HydStatic_HeelCurve.hxx>

namespace tnbLib
{

	class HydStatic_StaticStbCurve
		: public HydStatic_HeelCurve
	{

		/*Private Data*/

	public:

		HydStatic_StaticStbCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_StaticStbCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_StaticStbCurve
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);
	};
}

#endif // !_HydStatic_StaticStbCurve_Header
