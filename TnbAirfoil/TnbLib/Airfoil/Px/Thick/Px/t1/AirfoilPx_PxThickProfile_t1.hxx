#pragma once
#ifndef _AirfoilPx_PxThickProfile_t1_Header
#define _AirfoilPx_PxThickProfile_t1_Header

#include <AirfoilPx_PxThickProfile.hxx>

namespace tnbLib
{

	namespace profileLib
	{


		class PxThick_t1
			: public AirfoilPx_PxThickProfile
		{

			/*Private Data*/

			

			Standard_Real theMax_;
			Standard_Real theMaxLoc_;

			Standard_Real theLeadSteep_;
			Standard_Real theLeadSteepThight_;
			Standard_Real theLeadSteepWeight_;

			Standard_Real theTrailSteep_;
			Standard_Real theTrailSteepThight_;
			Standard_Real theTrailSteepWeight_;


			std::shared_ptr<Pln_Curve> theCurve_;


			// Private functions and operators [4/26/2023 Payvand]

			TnbAirfoil_EXPORT void Perform() override;

			TNB_SERIALIZATION(TnbAirfoil_EXPORT);

		public:

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_CHORDLEN;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_MAX;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_MAX_LOC;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LEAD_STEEP;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LEAD_STEEP_TIGHT;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LEAD_STEEP_WEIGHT;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_TRAIL_STEEP;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_TRAIL_STEEP_TIGHT;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_TRAIL_STEEP_WEIGHT;

			// default constructor [4/25/2023 Payvand]

			PxThick_t1()
				: theMax_(DEFAULT_MAX)
				, theMaxLoc_(DEFAULT_MAX_LOC)

				, theLeadSteep_(DEFAULT_LEAD_STEEP)
				, theLeadSteepThight_(DEFAULT_LEAD_STEEP_TIGHT)
				, theLeadSteepWeight_(DEFAULT_LEAD_STEEP_WEIGHT)

				, theTrailSteep_(DEFAULT_TRAIL_STEEP)
				, theTrailSteepThight_(DEFAULT_TRAIL_STEEP_TIGHT)
				, theTrailSteepWeight_(DEFAULT_TRAIL_STEEP_WEIGHT)
			{}


			// Public functions and operators [4/25/2023 Payvand]

			const auto& Curve() const
			{
				return theCurve_;
			}

			TnbAirfoil_EXPORT Standard_Real Value(const Standard_Real) const override;

			TnbAirfoil_EXPORT std::vector<std::shared_ptr<Pln_Curve>> Curves() const override;
			TnbAirfoil_EXPORT std::vector<Standard_Real> Spans() const override;
			
			auto Max() const { return theMax_; }
			auto MaxLoc() const { return theMaxLoc_; }

			auto LeadSteep() const { return theLeadSteep_; }
			auto LeadSteepTight() const { return theLeadSteepThight_; }
			auto LeadSteepWeight() const { return theLeadSteepWeight_; }

			auto TrailSteep() const { return theTrailSteep_; }
			auto TrailSteepTight() const { return theTrailSteepThight_; }
			auto TrailSteepWeight() const { return theTrailSteepWeight_; }
			
			void SetMax(const Standard_Real x) { theMax_ = x; }
			void SetMaxLoc(const Standard_Real x) { theMaxLoc_ = x; }

			void SetLeadSteep(const Standard_Real x) { theLeadSteep_ = x; }
			void SetLeadSteepTight(const Standard_Real x) { theLeadSteepThight_ = x; }
			void SetLeadSteepWeight(const Standard_Real x) { theLeadSteepWeight_ = x; }

			void SetTrailSteep(const Standard_Real x) { theTrailSteep_ = x; }
			void SetTrailSteepTight(const Standard_Real x) { theTrailSteepThight_ = x; }
			void SetTrailSteepWeight(const Standard_Real x) { theTrailSteepWeight_ = x; }

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::profileLib::PxThick_t1);

#endif // !_AirfoilPx_PxThickProfile_t1_Header
