#pragma once
#ifndef _HydStatic_DFldCurve_Header
#define _HydStatic_DFldCurve_Header

#include <HydStatic_HeelCurve.hxx>

namespace tnbLib
{

	class HydStatic_DFldCurve
		: public HydStatic_HeelCurve
	{

		/*Private Data*/

	public:

		HydStatic_DFldCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_DFldCurve
		(
			const Standard_Integer theIndex, 
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_DFldCurve
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const Handle(Geom2d_Curve)& theCurve
		);


		Standard_Real DownFloodingAngle() const;
	};
}

#endif // !_HydStatic_DFldCurve_Header
