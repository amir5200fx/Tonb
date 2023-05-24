#pragma once
#ifndef _AirfoilPx_NoseCurve_t1_Header
#define _AirfoilPx_NoseCurve_t1_Header

#include <AirfoilPx_NoseCurve.hxx>

namespace tnbLib
{

	namespace profileLib
	{

		class NoseCurve_t1
			: public AirfoilPx_NoseCurve
		{

			/*Private Data*/

			Standard_Real theUpperNoseTight_;
			Standard_Real theUpperMaxTight_;

			Standard_Real theLowerNoseTight_;
			Standard_Real theLowerMaxTight_;

		public:

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_NOSE_TIGHT;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_MAX_TIGHT;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_NOSE_TIGHT;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_MAX_TIGHT;

			// default constructor [5/5/2023 Payvand]

			NoseCurve_t1()
				: theUpperNoseTight_(DEFAULT_UPPER_NOSE_TIGHT)
				, theUpperMaxTight_(DEFAULT_UPPER_MAX_TIGHT)

				, theLowerNoseTight_(DEFAULT_LOWER_NOSE_TIGHT)
				, theLowerMaxTight_(DEFAULT_LOWER_MAX_TIGHT)
			{}

			// Constructors [5/5/2023 Payvand]

			// Public functions and operators [5/5/2023 Payvand]

			auto UpperNoseTight() const { return theUpperNoseTight_; }
			auto UpperMaxTight() const { return theUpperMaxTight_; }

			auto LowerNoseTight() const { return theLowerNoseTight_; }
			auto LowerMaxTight() const { return theLowerMaxTight_; }

			void SetUpperNoseTight(const Standard_Real x) { theUpperNoseTight_ = x; }
			void SetUpperMaxTight(const Standard_Real x) { theUpperMaxTight_ = x; }

			void SetLowerNoseTight(const Standard_Real x) { theLowerNoseTight_ = x; }
			void SetLowerMaxTight(const Standard_Real x) { theLowerMaxTight_ = x; }

			TnbAirfoil_EXPORT void Perform();

		};
	}
}

#endif // !_AirfoilPx_NoseCurve_t1_Header
