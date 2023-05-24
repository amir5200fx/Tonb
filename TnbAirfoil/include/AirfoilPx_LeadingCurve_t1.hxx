#pragma once
#ifndef _AirfoilPx_LeadingCurve_t1_Header
#define _AirfoilPx_LeadingCurve_t1_Header

#include <AirfoilPx_LeadingCurve.hxx>

namespace tnbLib
{

	namespace profileLib
	{

		class LeadingCurve_t1
			: public AirfoilPx_LeadingCurve
		{

			/*Private Data*/

			Standard_Real theNoseAngle_;

			Standard_Real theUpperTight_;
			Standard_Real theUpperWeight0_;
			Standard_Real theUpperWeight1_;
			Standard_Real theUpperWeight2_;

			Standard_Real theLowerTight_;
			Standard_Real theLowerWeight0_;
			Standard_Real theLowerWeight1_;
			Standard_Real theLowerWeight2_;

		public:

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_NOSE_ANGLE;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_TIGHT;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_WEIGHT0;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_WEIGHT1;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_WEIGHT2;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_TIGHT;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_WEIGHT0;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_WEIGHT1;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_WEIGHT2;

			// default constructor [5/6/2023 Payvand]

			LeadingCurve_t1()
				: theNoseAngle_(DEFAULT_NOSE_ANGLE)
				, theUpperTight_(DEFAULT_UPPER_TIGHT)
				, theUpperWeight0_(DEFAULT_UPPER_WEIGHT0)
				, theUpperWeight1_(DEFAULT_UPPER_WEIGHT1)
				, theUpperWeight2_(DEFAULT_UPPER_WEIGHT2)

				, theLowerTight_(DEFAULT_LOWER_TIGHT)
				, theLowerWeight0_(DEFAULT_LOWER_WEIGHT0)
				, theLowerWeight1_(DEFAULT_LOWER_WEIGHT1)
				, theLowerWeight2_(DEFAULT_LOWER_WEIGHT2)
			{}

			// constructors [5/6/2023 Payvand]


			// Public functions and operators [5/6/2023 Payvand]

			auto NoseAngle() const { return theNoseAngle_; }

			auto UpperTight() const { return theUpperTight_; }
			auto UpperWeight0() const { return theUpperWeight0_; }
			auto UpperWeight1() const { return theUpperWeight1_; }
			auto UpperWeight2() const { return theUpperWeight2_; }

			auto LowerTight() const { return theLowerTight_; }
			auto LowerWeight0() const { return theLowerWeight0_; }
			auto LowerWeight1() const { return theLowerWeight1_; }
			auto LowerWeight2() const { return theLowerWeight2_; }

			void SetNoseAngle(const Standard_Real x) { theNoseAngle_ = x; }

			void SetUpperTight(const Standard_Real x) { theUpperTight_ = x; }
			void SetUpperWeight0(const Standard_Real x) { theUpperWeight0_ = x; }
			void SetUpperWeight1(const Standard_Real x) { theUpperWeight1_ = x; }
			void SetUpperWeight2(const Standard_Real x) { theUpperWeight2_ = x; }

			void SetLowerTight(const Standard_Real x) { theLowerTight_ = x; }
			void SetLowerWeight0(const Standard_Real x) { theLowerWeight0_ = x; }
			void SetLowerWeight1(const Standard_Real x) { theLowerWeight1_ = x; }
			void SetLowerWeight2(const Standard_Real x) { theLowerWeight2_ = x; }

			TnbAirfoil_EXPORT void Perform();

		};
	}
}

#endif // !_AirfoilPx_LeadingCurve_t1_Header
