#pragma once
#ifndef _AirfoilPx_GlobalCurve_t1_Header
#define _AirfoilPx_GlobalCurve_t1_Header

#include <AirfoilPx_GlobalCurve.hxx>

namespace tnbLib
{

	namespace profileLib
	{

		class GlobalCurve_t1
			: public AirfoilPx_GlobalCurve
		{

			/*Private Data*/

			Standard_Real theUpperNoseTight_;
			Standard_Real theUpperMaxTight_;

			Standard_Real theUpperTrailAngle_;

			Standard_Real theUpperMaxVel_;
			Standard_Real theUpperTrailVel_;

			Standard_Real theLowerNoseTight_;
			Standard_Real theLowerMaxTight_;

			Standard_Real theLowerTrailAngle_;

			Standard_Real theLowerMaxVel_;
			Standard_Real theLowerTrailVel_;

		public:

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_NOSE_TIGHT;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_MAX_TIGHT;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_TRAIL_ANGLE;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_MAX_VEL;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_TRAIL_VEL;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_NOSE_TIGHT;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_MAX_TIGHT;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_TRAIL_ANGLE;

			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_MAX_VEL;
			static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_TRAIL_VEL;

			// default constructor [5/7/2023 Payvand]

			GlobalCurve_t1()
				: theUpperNoseTight_(DEFAULT_UPPER_NOSE_TIGHT)
				, theUpperMaxTight_(DEFAULT_UPPER_MAX_TIGHT)

				, theUpperTrailAngle_(DEFAULT_UPPER_TRAIL_ANGLE)

				, theUpperMaxVel_(DEFAULT_UPPER_MAX_VEL)
				, theUpperTrailVel_(DEFAULT_UPPER_TRAIL_VEL)

				, theLowerNoseTight_(DEFAULT_LOWER_NOSE_TIGHT)
				, theLowerMaxTight_(DEFAULT_LOWER_MAX_TIGHT)

				, theLowerTrailAngle_(DEFAULT_LOWER_TRAIL_ANGLE)

				, theLowerMaxVel_(DEFAULT_LOWER_MAX_VEL)
				, theLowerTrailVel_(DEFAULT_LOWER_TRAIL_VEL)
			{}

			// constructors [5/7/2023 Payvand]


			// Public functions and operators [5/7/2023 Payvand]

			auto UpperNoseTight() const { return theUpperNoseTight_; }
			auto UpperMaxTight() const { return theUpperMaxTight_; }

			auto UpperTrailAngle() const { return theUpperTrailAngle_; }
			
			auto UpperMaxVel() const { return theUpperMaxVel_; }
			auto UpperTrailVel() const { return theUpperTrailVel_; }

			auto LowerNoseTight() const { return theLowerNoseTight_; }
			auto LowerMaxTight() const { return theLowerMaxTight_; }

			auto LowerTrailAngle() const { return theLowerTrailAngle_; }

			auto LowerMaxVel() const { return theLowerMaxVel_; }
			auto LowerTrailVel() const { return theLowerTrailVel_; }

			void SetUpperNoseTight(const Standard_Real x) { theUpperNoseTight_ = x; }
			void SetUpperMaxTight(const Standard_Real x) { theUpperMaxTight_ = x; }

			void SetUpperTrailAngle(const Standard_Real x) { theUpperTrailAngle_ = x; }

			void SetUpperMaxVel(const Standard_Real x) { theUpperMaxVel_ = x; }
			void SetUpperTrailVel(const Standard_Real x) { theUpperTrailVel_ = x; }

			void SetLowerNoseTight(const Standard_Real x) { theLowerNoseTight_ = x; }
			void SetLowerMaxTight(const Standard_Real x) { theLowerMaxTight_ = x; }

			void SetLowerTrailAngle(const Standard_Real x) { theLowerTrailAngle_ = x; }

			void SetLowerMaxVel(const Standard_Real x) { theLowerMaxVel_ = x; }
			void SetLowerTrailVel(const Standard_Real x) { theLowerTrailVel_ = x; }

			TnbAirfoil_EXPORT void Perform();

		};
	}
}

#endif // !_AirfoilPx_GlobalCurve_t1_Header
