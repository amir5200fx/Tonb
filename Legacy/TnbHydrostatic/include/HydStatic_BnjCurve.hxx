#pragma once
#ifndef _HydStatic_BnjCurve_Header
#define _HydStatic_BnjCurve_Header

#include <HydStatic_HydCurve.hxx>

namespace tnbLib
{

	class HydStatic_BnjCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_HydCurve>(*this);
		}

	protected:


		//- default constructor for serializing 

		HydStatic_BnjCurve()
		{}

	public:


		//- constructors

		TnbHydStatic_EXPORT HydStatic_BnjCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_BnjCurve
		(
			Handle(Geom2d_Curve)&& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_BnjCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_BnjCurve
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Handle(Geom2d_Curve)& theCurve
		);


		//- public functions and operators

		TnbHydStatic_EXPORT Standard_Boolean IsIntersect
		(
			const Standard_Real theT
		) const;

		TnbHydStatic_EXPORT Standard_Real A0() const;

		TnbHydStatic_EXPORT Standard_Real A1() const;

		TnbHydStatic_EXPORT Standard_Real Value
		(
			const Standard_Real theT
		) const;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_BnjCurve);

#endif // !_HydStatic_BnjCurve_Header
