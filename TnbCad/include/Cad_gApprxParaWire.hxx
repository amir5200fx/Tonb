#pragma once
#ifndef _Cad_gApprxParaWire_Header
#define _Cad_gApprxParaWire_Header

#include <Cad_ApprxWire.hxx>
#include <Cad_gApprxParaWireFwd.hxx>
#include <Cad_gApprxParaCurve.hxx>
#include <Cad_Module.hxx>

namespace tnbLib
{

	template<>
	static TnbCad_EXPORT std::vector<std::shared_ptr<GModel_ParaCurve>> 
		Cad_gApprxParaWire::RetrieveCurves
		(
			const GModel_ParaWire&
		);
}

#endif // !_Cad_gApprxParaWire_Header
