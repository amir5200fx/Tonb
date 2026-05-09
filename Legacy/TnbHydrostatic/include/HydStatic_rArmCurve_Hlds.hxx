#pragma once
#ifndef _HydStatic_rArmCurve_Hlds_Header
#define _HydStatic_rArmCurve_Hlds_Header

#include <HydStatic_rArmCurve_Prim.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class rArmCurve_Hlds
			: public rArmCurve_Prim
		{

			/*Private Data*/

			Standard_Real theH_;


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<rArmCurve_Prim>(*this);
				ar & theH_;
			}

		protected:


			//- default constructor for serialization purposes

			rArmCurve_Hlds()
			{}


			//- constructors

			rArmCurve_Hlds
			(
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theCurve)
			{}

			rArmCurve_Hlds
			(
				Handle(Geom2d_Curve) && theCurve
			)
				: rArmCurve_Prim(std::move(theCurve))
			{}

			rArmCurve_Hlds
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Handle(Geom2d_Curve)& theCurve
			)
				: rArmCurve_Prim(theIndex, theName, theCurve)
			{}

			rArmCurve_Hlds
			(
				const Standard_Integer theIndex,
				const word& theName,
				Handle(Geom2d_Curve) && theCurve
			)
				: rArmCurve_Prim(theIndex, theName, std::move(theCurve))
			{}

		public:

			auto H() const
			{
				return theH_;
			}

			std::shared_ptr<HydStatic_rArmCurve>
				ExpandToPort() const override
			{
				NotImplemented;
				return nullptr;
			}

			void SetH(const Standard_Real theH)
			{
				theH_ = theH;
			}
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::hydStcLib::rArmCurve_Hlds);

#include <HydStatic_CurveMaker.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_SymmHeel<tnbLib::hydStcLib::rArmCurve_Hlds>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_AsymmHeel<tnbLib::hydStcLib::rArmCurve_Hlds>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_StbHeel<tnbLib::hydStcLib::rArmCurve_Hlds>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_ArbtHeel<tnbLib::hydStcLib::rArmCurve_Hlds>);

#include <HydStatic_rArmCurve_HldsIO.hxx>

#endif // !_HydStatic_rArmCurve_Hlds_Header
