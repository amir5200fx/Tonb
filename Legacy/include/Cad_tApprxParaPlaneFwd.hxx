#pragma once
#ifndef _Cad_tApprxParaPlaneFwd_Header
#define _Cad_tApprxParaPlaneFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/18/2022 Amir]
	template<class PlnType, bool RandSamples>
	class Cad_ApprxParaPlane;

	class TModel_Plane;

	typedef Cad_ApprxParaPlane<TModel_Plane, true> Cad_tApprxParaPlane;
}

#endif // !_Cad_tApprxParaPlaneFwd_Header
