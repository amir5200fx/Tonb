#pragma once
#ifndef _HydStatic_rAuCurve_Header
#define _HydStatic_rAuCurve_Header

#include <HydStatic_AuCurve.hxx>
#include <HydStatic_CurveMakerType.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_GzQ;

	class HydStatic_rAuCurve
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

		HydStatic_rAuCurve()
		{}

		TnbHydStatic_EXPORT HydStatic_rAuCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_rAuCurve
		(
			Handle(Geom2d_Curve)&& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_rAuCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve)&& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_rAuCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	public:

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_rAuCurve>
			AuCurve
			(
				const std::vector<HydStatic_GzQ>& theQs,
				const hydStcLib::CurveMakerType t
			);

	};
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_rAuCurve);

#include <HydStatic_CurveMaker.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_SymmHeel<tnbLib::HydStatic_rAuCurve>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_AsymmHeel<tnbLib::HydStatic_rAuCurve>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_StbHeel<tnbLib::HydStatic_rAuCurve>);
BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::CurveMaker_ArbtHeel<tnbLib::HydStatic_rAuCurve>);

#endif // !_HydStatic_rAuCurve_Header
