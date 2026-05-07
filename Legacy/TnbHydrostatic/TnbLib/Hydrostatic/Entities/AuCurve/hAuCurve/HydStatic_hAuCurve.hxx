#pragma once
#ifndef _HydStatic_hAuCurve_Header
#define _HydStatic_hAuCurve_Header

#include <HydStatic_AuCurve.hxx>
#include <HydStatic_CurveMakerType.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_GzQ;

	class HydStatic_hAuCurve
		: public HydStatic_AuCurve
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_AuCurve>(*this);
		}

	protected:

		HydStatic_hAuCurve()
		{}

		TnbHydStatic_EXPORT HydStatic_hAuCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_hAuCurve
		(
			Handle(Geom2d_Curve)&& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_hAuCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve)&& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_hAuCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	public:

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_hAuCurve>
			AuCurve
			(
				const std::vector<HydStatic_GzQ>& theQs,
				const hydStcLib::CurveMakerType t
			);
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_hAuCurve);

#include <HydStatic_CurveMaker.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_SymmHeel<tnbLib::HydStatic_hAuCurve>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_AsymmHeel<tnbLib::HydStatic_hAuCurve>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_StbHeel<tnbLib::HydStatic_hAuCurve>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_ArbtHeel<tnbLib::HydStatic_hAuCurve>);

#endif // !_HydStatic_hAuCurve_Header
