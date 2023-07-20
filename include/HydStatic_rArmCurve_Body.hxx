#pragma once
#ifndef _HydStatic_rArmCurve_Body_Header
#define _HydStatic_rArmCurve_Body_Header

#include <HydStatic_rArmCurve_Prim.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class rArmCurve_Body
			: public rArmCurve_Prim
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<rArmCurve_Prim>(*this);
			}

		protected:


			//- default constructor for serialization purposes

			rArmCurve_Body()
			{}


			//- constructors

			rArmCurve_Body
			(
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theCurve)
			{}

			/*rArmCurve_Body
			(
				const Standard_Integer theIndex,
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theIndex, theCurve)
			{}*/

			rArmCurve_Body
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theIndex, theName, theCurve)
			{}

		public:

			std::shared_ptr<HydStatic_rArmCurve>
				ExpandToPort() const override
			{
				NotImplemented;
				return nullptr;
			}
		};
	}
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::hydStcLib::rArmCurve_Body);


#include <HydStatic_CurveMaker.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_SymmHeel<tnbLib::hydStcLib::rArmCurve_Body>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_AsymmHeel<tnbLib::hydStcLib::rArmCurve_Body>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_StbHeel<tnbLib::hydStcLib::rArmCurve_Body>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_ArbtHeel<tnbLib::hydStcLib::rArmCurve_Body>);

#include <HydStatic_rArmCurve_BodyIO.hxx>

#endif // !_HydStatic_rArmCurve_Body_Header
