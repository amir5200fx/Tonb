#pragma once
#ifndef _Cad_tApprxParaWireFwd_Header
#define _Cad_tApprxParaWireFwd_Header

namespace tnbLib
{

	// Forward Declarations [6/21/2022 Amir]
	template<class WireType, bool RandSamples>
	class Cad_ApprxWire;

	class TModel_ParaWire;

	typedef Cad_ApprxWire<TModel_ParaWire, true> Cad_tApprxParaWire;
}

#endif // !_Cad_tApprxParaWireFwd_Header
