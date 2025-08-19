#pragma once
#ifndef _Cad_gCommonSingularityFwd_Header
#define _Cad_gCommonSingularityFwd_Header

namespace tnbLib
{

	// Forward Declarations [6/9/2022 Amir]
	template<class SurfType>
	class Cad_CommonSingularity;

	class GModel_Surface;

	typedef Cad_CommonSingularity<GModel_Surface> Cad_gCommonSingularity;
}

#endif // !_Cad_gCommonSingularityFwd_Header
