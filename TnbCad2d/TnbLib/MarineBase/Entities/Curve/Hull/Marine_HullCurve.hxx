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


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_PlnCurve>(*this);
		}

	protected:

		//- default constructor

		TnbCad2d_EXPORT Marine_HullCurve();


		//- constructors

		TnbCad2d_EXPORT Marine_HullCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbCad2d_EXPORT explicit Marine_HullCurve
		(
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbCad2d_EXPORT Marine_HullCurve
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

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_HullCurve);

#endif // !_Marine_HullCurve_Header
