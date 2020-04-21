#include <ISC08_Factor.hxx>

namespace tnbLib
{

	const isc08Lib::P isc08Lib::windPressure = isc08Lib::P(504.0);
	const isc08Lib::g isc08Lib::gravAccel = isc08Lib::g(9.81);

	const Standard_Real isc08Lib::max_B_per_d = (Standard_Real)3.5;
	const Standard_Real isc08Lib::min_KG_per_d_minus_1 = (Standard_Real)0.3;
	const Standard_Real isc08Lib::max_KG_per_d_minus_1 = (Standard_Real)0.5;
	const Standard_Real isc08Lib::max_T = (Standard_Real)20.0;
}