#pragma once
#ifndef _Cad_gSingularityBaseFwd_Header
#define _Cad_gSingularityBaseFwd_Header

namespace tnbLib
{

	// Forward Declarations [3/30/2022 Amir]
	template<class CurveType>
	class Cad_SingularityBase;

	class GModel_ParaCurve;

	typedef Cad_SingularityBase<GModel_ParaCurve> Cad_gSingularityBase;
}

#endif // !_Cad_gSingularityBaseFwd_Header
