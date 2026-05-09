#pragma once
#ifndef _AirfoilPx_GlobalCurve_Header
#define _AirfoilPx_GlobalCurve_Header

#include <AirfoilPx_Curve.hxx>

namespace tnbLib
{

	class AirfoilPx_GlobalCurve
		: public AirfoilPx_Curve
	{

		/*Private Data*/

		Standard_Real theXo_;
		Standard_Real theYo_;

		Standard_Real theNoseAngle_;

		Standard_Real theChordLen_;

		Standard_Real theUpperMax_;
		Standard_Real theUpperMaxLoc_;

		Standard_Real theLowerMax_;
		Standard_Real theLowerMaxLoc_;

	public:

		static TnbAirfoil_EXPORT Standard_Real DEFAULT_XO;
		static TnbAirfoil_EXPORT Standard_Real DEFAULT_YO;

		static TnbAirfoil_EXPORT Standard_Real DEFAULT_NOSE_ANGLE;

		static TnbAirfoil_EXPORT Standard_Real DEFAULT_CHORD_LEN;

		static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_MAX;
		static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_MAX_LOC;
		static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_MAX;
		static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_MAX_LOC;

	protected:

		// default constructor [5/7/2023 Payvand]

		AirfoilPx_GlobalCurve()
			: theXo_(DEFAULT_XO)
			, theYo_(DEFAULT_YO)
			, theNoseAngle_(DEFAULT_NOSE_ANGLE)
			, theChordLen_(DEFAULT_CHORD_LEN)
			, theUpperMax_(DEFAULT_UPPER_MAX)
			, theUpperMaxLoc_(DEFAULT_UPPER_MAX_LOC)
			, theLowerMax_(DEFAULT_LOWER_MAX)
			, theLowerMaxLoc_(DEFAULT_LOWER_MAX_LOC)
		{}

		// constructors [5/7/2023 Payvand]


	public:


		// Public functions and operators [5/7/2023 Payvand]

		auto Xo() const { return theXo_; }
		auto Yo() const { return theYo_; }

		auto ChordLen() const { return theChordLen_; }

		auto NoseAngle() const { return theNoseAngle_; }

		auto UpperMax() const { return theUpperMax_; }
		auto UpperMaxLoc() const { return theUpperMaxLoc_; }
		auto LowerMax() const { return theLowerMax_; }
		auto LowerMaxLoc() const { return theLowerMaxLoc_; }

		void SetXo(const Standard_Real x) { theXo_ = x; }
		void SetYo(const Standard_Real x) { theYo_ = x; }

		void SetChordLen(const Standard_Real x) { theChordLen_ = x; }

		void SetNoseAngle(const Standard_Real x) { theNoseAngle_ = x; }

		void SetUpperMax(const Standard_Real x) { theUpperMax_ = x; }
		void SetUpperMaxLoc(const Standard_Real x) { theUpperMaxLoc_ = x; }
		void SetLowerMax(const Standard_Real x) { theLowerMax_ = x; }
		void SetLowerMaxLoc(const Standard_Real x) { theLowerMaxLoc_ = x; }

	};
}

#endif // !_AirfoilPx_GlobalCurve_Header
