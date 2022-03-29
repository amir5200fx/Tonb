#pragma once
#ifndef _Cad_gSingularityFwd_Header
#define _Cad_gSingularityFwd_Header

namespace tnbLib
{

	// Forward Declarations [3/28/2022 Amir]
	template<class SurfType>
	class Cad_Singularity;

	class GModel_Surface;

	typedef Cad_Singularity<GModel_Surface> Cad_gSingularity;
}

#endif // !_Cad_gSingularityFwd_Header
