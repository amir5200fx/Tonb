#pragma once
#ifndef _Cad_gApprxParaCurveFwd_Header
#define _Cad_gApprxParaCurveFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/4/2022 Amir]
	template<class CurveType, bool RandSamples>
	class Cad_ApprxCurve;

	class GModel_ParaCurve;

	typedef Cad_ApprxCurve<GModel_ParaCurve, true>
		Cad_gApprxParaCurve;
}

#endif // !_Cad_gApprxParaCurveFwd_Header
