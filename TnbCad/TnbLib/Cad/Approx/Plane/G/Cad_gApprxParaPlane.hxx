#pragma once
#ifndef _Cad_gApprxParaPlane_Header
#define _Cad_gApprxParaPlane_Header

#include <Cad_ApprxParaPlane.hxx>
#include <Cad_gApprxParaPlaneFwd.hxx>
#include <Cad_gApprxParaWire.hxx>

namespace tnbLib
{

	template<>
	TnbCad_EXPORT std::vector<std::shared_ptr<GModel_ParaWire>> 
		Cad_gApprxParaPlane::RetrieveWires
		(
			const std::shared_ptr<tnbLib::GModel_Plane>&
		);
}

#endif // !_Cad_gApprxParaPlane_Header
