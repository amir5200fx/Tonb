#pragma once
#ifndef _HydStatic_hArmCurve_Header
#define _HydStatic_hArmCurve_Header

#include <HydStatic_ArmCurve.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_hAuCurve;
	class HydStatic_CmptLib;

	class HydStatic_hArmCurve
		: public HydStatic_ArmCurve
	{

		friend class HydStatic_CmptLib;

		/*Private Data*/

		std::shared_ptr<HydStatic_hAuCurve> theAuCurve_;


		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

		auto& ChangeAuCurve()
		{
			return theAuCurve_;
		}

	protected:


		HydStatic_hArmCurve()
		{}


		TnbHydStatic_EXPORT HydStatic_hArmCurve
		(
			Handle(Geom2d_Curve)&& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_hArmCurve
		(
			const Handle(Geom2d_Curve) & theCurve
		);

		TnbHydStatic_EXPORT HydStatic_hArmCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve)&& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_hArmCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);


	public:

		Standard_Boolean HasAuCurve() const
		{
			return (Standard_Boolean)theAuCurve_;
		}
		
		const auto& AuCurve() const
		{
			return theAuCurve_;
		}

		void SetAuCurve
		(
			const std::shared_ptr<HydStatic_hAuCurve>&& theCurve
		)
		{
			theAuCurve_ = std::move(theCurve);
		}
		
	};
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_hArmCurve);


#include <HydStatic_CurveMaker.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_SymmHeel<tnbLib::HydStatic_hArmCurve>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_AsymmHeel<tnbLib::HydStatic_hArmCurve>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_StbHeel<tnbLib::HydStatic_hArmCurve>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_ArbtHeel<tnbLib::HydStatic_hArmCurve>);

#endif // !_HydStatic_hArmCurve_Header
