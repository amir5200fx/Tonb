#pragma once
#ifndef _HydStatic_CrsCurveQ_Header
#define _HydStatic_CrsCurveQ_Header

#include <HydStatic_HydOffsetCurve.hxx>

namespace tnbLib
{

	class HydStatic_CrsCurveQ
		: public HydStatic_HydOffsetCurve
	{

		/*Private Data*/

		Standard_Real theHeel_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_HydOffsetCurve>(*this);
			ar & theHeel_;
		}

	protected:

		//- default constructor

		HydStatic_CrsCurveQ()
		{}


		//- constructors

		HydStatic_CrsCurveQ
		(
			const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
		)
			: HydStatic_HydOffsetCurve(theQs)
		{}

		HydStatic_CrsCurveQ
		(
			std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
		)
			: HydStatic_HydOffsetCurve(std::move(theQs))
		{}

		HydStatic_CrsCurveQ
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
		)
			: HydStatic_HydOffsetCurve(theIndex, theName, theQs)
		{}

		HydStatic_CrsCurveQ
		(
			const Standard_Integer theIndex,
			const word& theName, 
			std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
		)
			: HydStatic_HydOffsetCurve(theIndex, theName, std::move(theQs))
		{}


	public:

		//- public functions and operators

		auto Heel() const
		{
			return theHeel_;
		}

		TnbHydStatic_EXPORT Standard_Real LeverArm0() const;
		TnbHydStatic_EXPORT Standard_Real LeverArm1() const;

		TnbHydStatic_EXPORT Standard_Real Dispv0() const;
		TnbHydStatic_EXPORT Standard_Real Dispv1() const;

		TnbHydStatic_EXPORT Standard_Real LeverArm(const Standard_Real theVolume) const;

		void SetHeel
		(
			const Standard_Real theHeel
		)
		{
			theHeel_ = theHeel;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_CrsCurveQ);

#include <HydStatic_CurveQMaker.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveQMaker_SymmHeel<tnbLib::HydStatic_CrsCurveQ>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveQMaker_AsymmHeel<tnbLib::HydStatic_CrsCurveQ>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveQMaker_StbHeel<tnbLib::HydStatic_CrsCurveQ>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveQMaker_ArbtHeel<tnbLib::HydStatic_CrsCurveQ>);

#endif // !_HydStatic_CrsCurveQ_Header
