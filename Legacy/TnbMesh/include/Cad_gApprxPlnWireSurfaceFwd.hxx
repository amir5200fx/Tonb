#pragma once
#ifndef _Cad_gApprxPlnWireSurfaceFwd_Header
#define _Cad_gApprxPlnWireSurfaceFwd_Header

#include <Aft2d_gPlnWireSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/17/2022 Amir]
	template<class WireType, bool RandSamples>
	class Cad_ApprxWire;

	typedef Cad_ApprxWire<Aft2d_gPlnWireSurface, true> Cad_gApprxPlnWireSurface;
}

#endif // !_Cad_gApprxPlnWireSurfaceFwd_Header
