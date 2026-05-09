#pragma once
#ifndef _HydStatic_rArmCurve_Prim_Header
#define _HydStatic_rArmCurve_Prim_Header

#include <HydStatic_rArmCurve.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class rArmCurve_Prim
			: public HydStatic_rArmCurve
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<HydStatic_rArmCurve>(*this);
			}

		protected:

			//- default constructor for serialization purposes

			rArmCurve_Prim()
			{}


			//- constructors

			rArmCurve_Prim
			(
				const Handle(Geom2d_Curve)& theCurve
			)
				: HydStatic_rArmCurve(theCurve)
			{}

			/*rArmCurve_Prim
			(
				const Standard_Integer theIndex,
				const Handle(Geom2d_Curve)& theCurve
			)
				: HydStatic_rArmCurve(theIndex, theCurve)
			{}*/

			rArmCurve_Prim
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Handle(Geom2d_Curve)& theCurve
			)
				: HydStatic_rArmCurve(theIndex, theName, theCurve)
			{}

		public:

			Standard_Boolean IsPrim() const override
			{
				return Standard_True;
			}

		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::hydStcLib::rArmCurve_Prim);

#endif // !_HydStatic_rArmCurve_Prim_Header
