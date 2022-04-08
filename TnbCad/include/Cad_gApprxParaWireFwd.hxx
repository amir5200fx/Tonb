#pragma once
#ifndef _Cad_gApprxParaWireFwd_Header
#define _Cad_gApprxParaWireFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/4/2022 Amir]
	template<class WireType, bool RandSamples>
	class Cad_ApprxWire;

	class GModel_ParaWire;

	typedef Cad_ApprxWire<GModel_ParaWire, true> Cad_gApprxParaWire;
}

#endif // !_Cad_gApprxParaWireFwd_Header
