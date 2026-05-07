#pragma once
#ifndef _Cad_tApprxParaWire_Header
#define _Cad_tApprxParaWire_Header

#include <Cad_ApprxWire.hxx>
#include <Cad_tApprxParaWireFwd.hxx>
#include <Cad_tApprxParaCurve.hxx>
#include <Cad_Module.hxx>

namespace tnbLib
{

	template<>
	static TnbCad_EXPORT std::vector<std::shared_ptr<TModel_ParaCurve>>
		Cad_tApprxParaWire::RetrieveCurves
		(
			const TModel_ParaWire&
		);
}

#endif // !_Cad_tApprxParaWire_Header
