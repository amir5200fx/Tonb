#pragma once
#ifndef _ISC08_CmptLib_Header
#define _ISC08_CmptLib_Header

#include <ISC08_Factor.hxx>
#include <ISC08_Parameter.hxx>
#include <Marine_VesselParams.hxx>

namespace tnbLib
{

	class ISC08_CmptLib
	{

	public:

		static TnbISC08_EXPORT isc08Lib::Phi 
			CalcAngleOfRoll
			(
				const marineLib::B& B,
				const marineLib::TM& d,
				const marineLib::CB& CB, 
				const marineLib::LWL& lwl, 
				const marineLib::KG& KG, 
				const isc08Lib::Ak& Ak,
				const isc08Lib::T& T,
				const isc08Lib::BilgeBarCondition cond
			);

		static TnbISC08_EXPORT isc08Lib::Lw
			CalcWindHeelingLever
			(
				const isc08Lib::P& theP, 
				const isc08Lib::A& theArea, 
				const isc08Lib::Z& theZ, 
				const isc08Lib::g& theG,
				const marineLib::DISPM& theDispm
			);

		static TnbISC08_EXPORT isc08Lib::Lw
			CalcGustWind
			(
				const isc08Lib::Lw& theLw
			);

		static TnbISC08_EXPORT isc08Lib::T
			CalcRollingPeriod
			(
				const marineLib::B& B,
				const marineLib::TM& d, 
				const marineLib::LWL& lwl,
				const marineLib::GM& gm
			);
	};
}

#endif // !_ISC08_CmptLib_Header
