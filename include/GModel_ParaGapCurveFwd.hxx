#pragma once
#ifndef _GModel_ParaGapCurveFwd_Header
#define _GModel_ParaGapCurveFwd_Header

namespace tnbLib
{

	// Forward Declarations [5/12/2022 Amir]
	template<class CurveType>
	class Cad_ParaGapCurve;

	class GModel_ParaCurve;

	typedef Cad_ParaGapCurve<GModel_ParaCurve>
		GModel_ParaGapCurve;
}

#endif // !_GModel_ParaGapCurveFwd_Header
