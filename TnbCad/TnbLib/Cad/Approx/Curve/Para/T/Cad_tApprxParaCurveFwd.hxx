#pragma once
#ifndef _Cad_tApprxParaCurveFwd_Header
#define _Cad_tApprxParaCurveFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/4/2022 Amir]
	template<class CurveType, bool RandSamples>
	class Cad_ApprxCurve;

	class TModel_ParaCurve;

	typedef Cad_ApprxCurve<TModel_ParaCurve, true>
		Cad_tApprxParaCurve;
}

#endif // !_Cad_tApprxParaCurveFwd_Header
