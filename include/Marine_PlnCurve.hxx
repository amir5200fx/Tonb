#pragma once
#ifndef _Marine_PlnCurve_Header
#define _Marine_PlnCurve_Header

#include <Pln_Curve.hxx>

namespace tnbLib
{

	class Marine_PlnCurve
		: public Pln_Curve
	{

		/*Private Data*/


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Pln_Curve>(*this);
		}

	protected:

		Marine_PlnCurve();

		Marine_PlnCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeom
		);

		Marine_PlnCurve
		(
			const Handle(Geom2d_Curve)& theGeom
		);

		Marine_PlnCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom
		);

	public:

		Standard_Boolean IsMarine() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsOnTank() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsOnSail() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsOnHull() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsOnWater() const
		{
			return Standard_False;
		}
	};
}

#endif // !_Marine_PlnCurve_Header
