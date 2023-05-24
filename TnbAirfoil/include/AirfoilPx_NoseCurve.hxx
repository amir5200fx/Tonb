#pragma once
#ifndef _AirfoilPx_NoseCurve_Header
#define _AirfoilPx_NoseCurve_Header

#include <AirfoilPx_Curve.hxx>

namespace tnbLib
{

	class AirfoilPx_NoseCurve
		: public AirfoilPx_Curve
	{

		/*Private Data*/

		Standard_Real theXo_;
		Standard_Real theYo_;

		Standard_Real theUpperMax_;
		Standard_Real theUpperMaxLoc_;

		Standard_Real theLowerMax_;
		Standard_Real theLowerMaxLoc_;

	public:

		static TnbAirfoil_EXPORT Standard_Real DEFAULT_XO;
		static TnbAirfoil_EXPORT Standard_Real DEFAULT_YO;

		static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_MAX;
		static TnbAirfoil_EXPORT Standard_Real DEFAULT_UPPER_MAX_LOC;
		static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_MAX;
		static TnbAirfoil_EXPORT Standard_Real DEFAULT_LOWER_MAX_LOC;

	protected:

		// default constructor [5/5/2023 Payvand]

		AirfoilPx_NoseCurve()
			: theXo_(DEFAULT_XO)
			, theYo_(DEFAULT_YO)
			, theUpperMax_(DEFAULT_UPPER_MAX)
			, theUpperMaxLoc_(DEFAULT_UPPER_MAX_LOC)
			, theLowerMax_(DEFAULT_LOWER_MAX)
			, theLowerMaxLoc_(DEFAULT_LOWER_MAX_LOC)
		{}

		// constructors [5/5/2023 Payvand]

	public:

		

		// Public functions and operators [5/5/2023 Payvand]

		auto Xo() const { return theXo_; }
		auto Yo() const { return theYo_; }

		auto UpperMax() const { return theUpperMax_; }
		auto UpperMaxLoc() const { return theUpperMaxLoc_; }
		auto LowerMax() const { return theLowerMax_; }
		auto LowerMaxLoc() const { return theLowerMaxLoc_; }

		void SetXo(const Standard_Real x) { theXo_ = x; }
		void SetYo(const Standard_Real x) { theYo_ = x; }

		void SetUpperMax(const Standard_Real x) { theUpperMax_ = x; }
		void SetUpperMaxLoc(const Standard_Real x) { theUpperMaxLoc_ = x; }
		void SetLowerMax(const Standard_Real x) { theLowerMax_ = x; }
		void SetLowerMaxLoc(const Standard_Real x) { theLowerMaxLoc_ = x; }

	};
}

#endif // !_AirfoilPx_NoseCurve_Header
