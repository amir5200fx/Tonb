#pragma once
#ifndef _Cad_gApprxParaPlaneFwd_Header
#define _Cad_gApprxParaPlaneFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/18/2022 Amir]
	template<class PlnType, bool RandSamples>
	class Cad_ApprxParaPlane;

	class GModel_Plane;

	typedef Cad_ApprxParaPlane<GModel_Plane, true> Cad_gApprxParaPlane;
}

#endif // !_Cad_gApprxParaPlaneFwd_Header
