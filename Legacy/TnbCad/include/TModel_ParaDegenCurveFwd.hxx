#pragma once
#ifndef _TModel_ParaDegenCurveFwd_Header
#define _TModel_ParaDegenCurveFwd_Header

namespace tnbLib
{

	// Forward Declarations [12/12/2022 Payvand]
	template<class CurveType>
	class Cad_ParaDegenCurve;

	class TModel_ParaCurve;

	typedef Cad_ParaDegenCurve<TModel_ParaCurve>
		TModel_ParaDegenCurve;
}

#endif // !_TModel_ParaDegenCurveFwd_Header
