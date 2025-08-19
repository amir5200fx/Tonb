#pragma once
#ifndef _AirfoilPx_PxThickProfile_t2_Header
#define _AirfoilPx_PxThickProfile_t2_Header

#include <AirfoilPx_PxThickProfile.hxx>

namespace tnbLib
{

	namespace profileLib
	{

		class PxThick_t2
			: public AirfoilPx_PxThickProfile
		{

			/*Private Data*/

			Standard_Real theMax_;
			Standard_Real theMaxLoc_;

			Standard_Real theLeadSteepTight1_;
			Standard_Real theLeadSteepTight2_;

			Standard_Real theTrailSteepTight_;
			Standard_Real theTrailSteep_;
			Standard_Real theTrailSteepVelocity_;

			std::shared_ptr<Pln_Curve> theCurve_;


			// Private functions and operators [4/26/2023 Payvand]

			TnbAirfoil_EXPORT void Perform() override;

			TNB_SERIALIZATION(TnbAirfoil_EXPORT);

		public:

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_CHORDLEN;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_MAX;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_MAX_LOC;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LEAD_STEEP_TIGHT1;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LEAD_STEEP_TIGHT2;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_TRAIL_STEEP_TIGHT;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_TRAIL_STEEP;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_TRAIL_STEEP_VELOCITY;

			// default constructor [4/30/2023 Payvand]

			PxThick_t2()
				: theMax_(DEFAULT_MAX)
				, theMaxLoc_(DEFAULT_MAX_LOC)

				, theLeadSteepTight1_(DEFAULT_LEAD_STEEP_TIGHT1)
				, theLeadSteepTight2_(DEFAULT_LEAD_STEEP_TIGHT2)

				, theTrailSteepTight_(DEFAULT_TRAIL_STEEP_TIGHT)
				, theTrailSteep_(DEFAULT_TRAIL_STEEP)
				, theTrailSteepVelocity_(DEFAULT_TRAIL_STEEP_VELOCITY)
			{}

			// Public functions and operators [4/30/2023 Payvand]

			const auto& Curve() const
			{
				return theCurve_;
			}

			TnbAirfoil_EXPORT Standard_Real Value(const Standard_Real) const override;

			TnbAirfoil_EXPORT std::vector<std::shared_ptr<Pln_Curve>> Curves() const override;
			TnbAirfoil_EXPORT std::vector<Standard_Real> Spans() const override;

			auto Max() const { return theMax_; }
			auto MaxLoc() const { return theMaxLoc_; }

			auto LeadSteepTight1() const { return theLeadSteepTight1_; }
			auto LeadSteepTight2() const { return theLeadSteepTight2_; }

			auto TrailSteepTight() const { return theTrailSteepTight_; }
			auto TrailSteep() const { return theTrailSteep_; }
			auto TrailSteepVelocity() const { return theTrailSteepVelocity_; }

			void SetMax(const Standard_Real x) { theMax_ = x; }
			void SetMaxLoc(const Standard_Real x) { theMaxLoc_ = x; }

			void SetLeadSteepTight1(const Standard_Real x) { theLeadSteepTight1_ = x; }
			void SetLeadSteepTight2(const Standard_Real x) { theLeadSteepTight2_ = x; }

			void SetTrailSteepTight(const Standard_Real x) { theTrailSteepTight_ = x; }
			void SetTrailSteep(const Standard_Real x) { theTrailSteep_ = x; }
			void SetTrailSteepVelocity(const Standard_Real x) { theTrailSteepVelocity_ = x; }

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::profileLib::PxThick_t2);

#endif // !_AirfoilPx_PxThickProfile_t2_Header
