#pragma once
#ifndef _TModel_ParaGapCurveFwd_Header
#define _TModel_ParaGapCurveFwd_Header

namespace tnbLib
{

	// Forward Declarations [6/21/2022 Amir]
	template<class CurveType>
	class Cad_ParaGapCurve;

	class TModel_ParaCurve;

	typedef Cad_ParaGapCurve<TModel_ParaCurve>
		TModel_ParaGapCurve;
}

#endif // !_TModel_ParaGapCurveFwd_Header
