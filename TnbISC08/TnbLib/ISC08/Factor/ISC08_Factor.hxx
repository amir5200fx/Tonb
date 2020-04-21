#pragma once
#ifndef _ISC08_Factor_Header
#define _ISC08_Factor_Header

#include <Standard_Real.hxx>
#include <ISC08_Parameter.hxx>

namespace tnbLib
{

	namespace isc08Lib
	{

		enum class BilgeBarCondition
		{
			round_bilged_or_having_no_bilge_or_bar_keels,
			sharp_bilges,
			others
		};

		extern const isc08Lib::P windPressure;
		extern const isc08Lib::g gravAccel;

		extern const Standard_Real max_B_per_d;
		extern const Standard_Real min_KG_per_d_minus_1;
		extern const Standard_Real max_KG_per_d_minus_1;
		extern const Standard_Real max_T;
	}
}

#endif // !_ISC08_Factor_Header
