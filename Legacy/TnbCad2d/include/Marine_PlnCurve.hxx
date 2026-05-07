#pragma once
#ifndef _Marine_PlnCurve_Header
#define _Marine_PlnCurve_Header

#include <Pln_Curve.hxx>
#include <Cad2d_Module.hxx>
#include <Marine_PlnCurveType.hxx>

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

		TnbCad2d_EXPORT Marine_PlnCurve();

		TnbCad2d_EXPORT Marine_PlnCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbCad2d_EXPORT Marine_PlnCurve
		(
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbCad2d_EXPORT Marine_PlnCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom
		);

		Marine_PlnCurve(Pln_Curve&& theCurve)
			: Pln_Curve(std::move(theCurve))
		{}

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

		virtual marineLib::curveType CurveType() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_PlnCurve);

#endif // !_Marine_PlnCurve_Header
