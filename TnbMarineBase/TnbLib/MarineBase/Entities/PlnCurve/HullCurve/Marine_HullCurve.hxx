#pragma once
#ifndef _Marine_HullCurve_Header
#define _Marine_HullCurve_Header

#include <Marine_PlnCurve.hxx>

namespace tnbLib
{

	class Marine_HullCurve
		: public Marine_PlnCurve
	{

		/*Private Data*/

	protected:

		Marine_HullCurve();

		Marine_HullCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeom
		);

		Marine_HullCurve
		(
			const Handle(Geom2d_Curve)& theGeom
		);

		Marine_HullCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom
		);


		Standard_Boolean IsOnHull() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsDry() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsWetted() const
		{
			return Standard_False;
		}

	};
}

#endif // !_Marine_HullCurve_Header
