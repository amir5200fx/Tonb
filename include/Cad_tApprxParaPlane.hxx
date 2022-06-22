#pragma once
#ifndef _Cad_tApprxParaPlane_Header
#define _Cad_tApprxParaPlane_Header

#include <Cad_ApprxParaPlane.hxx>
#include <Cad_tApprxParaPlaneFwd.hxx>
#include <Cad_tApprxParaWire.hxx>

namespace tnbLib
{

	template<>
	TnbCad_EXPORT std::vector<std::shared_ptr<TModel_ParaWire>>
		Cad_tApprxParaPlane::RetrieveWires
		(
			const std::shared_ptr<tnbLib::TModel_Plane>&
		);
}

#endif // !_Cad_tApprxParaPlane_Header
