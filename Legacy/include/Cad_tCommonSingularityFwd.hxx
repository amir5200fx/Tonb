#pragma once
#ifndef _Cad_tCommonSingularityFwd_Header
#define _Cad_tCommonSingularityFwd_Header

namespace tnbLib
{

	// Forward Declarations [6/21/2022 Amir]
	template<class SurfType>
	class Cad_CommonSingularity;

	class TModel_Surface;

	typedef Cad_CommonSingularity<TModel_Surface> Cad_tCommonSingularity;
}

#endif // !_Cad_tCommonSingularityFwd_Header
