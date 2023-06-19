#pragma once
#ifndef _HydStatic_rArmCurve_LDT_Header
#define _HydStatic_rArmCurve_LDT_Header

#include <HydStatic_rArmCurve_Prim.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class rArmCurve_LDT
			: public rArmCurve_Prim
		{

			/*Private Data*/

			Standard_Real theD_;


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<rArmCurve_Prim>(*this);
				ar & theD_;
			}

		protected:


			//- default constructor for serialization purposes

			rArmCurve_LDT()
			{}


			//- constructors

			rArmCurve_LDT
			(
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theCurve)
			{}

			rArmCurve_LDT
			(
				Handle(Geom2d_Curve)&& theCurve
			)
				: rArmCurve_Prim(std::move(theCurve))
			{}

			/*rArmCurve_LDT
			(
				const Standard_Integer theIndex, 
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theD
			)
				: rArmCurve_Prim(theIndex, theCurve)
				, theD_(theD)
			{}*/

			rArmCurve_LDT
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theIndex, theName, theCurve)
			{}

			rArmCurve_LDT
			(
				const Standard_Integer theIndex,
				const word& theName,
				Handle(Geom2d_Curve)&& theCurve
			)
				: rArmCurve_Prim(theIndex, theName, std::move(theCurve))
			{}

		public:

			auto D() const
			{
				return theD_;
			}

			std::shared_ptr<HydStatic_rArmCurve> ExpandToPort() const override
			{
				NotImplemented;
				return nullptr;
			}

			void SetD(const Standard_Real theD)
			{
				theD_ = theD;
			}
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::hydStcLib::rArmCurve_LDT);


#include <HydStatic_CurveMaker.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_SymmHeel<tnbLib::hydStcLib::rArmCurve_LDT>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_AsymmHeel<tnbLib::hydStcLib::rArmCurve_LDT>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_StbHeel<tnbLib::hydStcLib::rArmCurve_LDT>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_ArbtHeel<tnbLib::hydStcLib::rArmCurve_LDT>);

#include <HydStatic_rArmCurve_LDTIO.hxx>

#endif // !_HydStatic_rArmCurve_LDT_Header
