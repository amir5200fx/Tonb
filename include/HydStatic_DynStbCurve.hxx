#pragma once
#ifndef _HydStatic_DynStbCurve_Header
#define _HydStatic_DynStbCurve_Header

#include <HydStatic_HeelCurve.hxx>

namespace tnbLib
{

	class HydStatic_DynStbCurve
		: public HydStatic_HeelCurve
	{

		/*Private Data*/

	public:

		HydStatic_DynStbCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_DynStbCurve
		(
			const Standard_Integer theIndex, 
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_DynStbCurve
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Handle(Geom2d_Curve)& theCurve
		);

	};
}

#endif // !_HydStatic_DynStbCurve_Header
