#pragma once
#ifndef _Cad_gSingularityTopologyFwd_Header
#define _Cad_gSingularityTopologyFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/21/2022 Amir]
	template<class SurfType>
	class Cad_SingularityTopology;

	class GModel_Surface;

	typedef Cad_SingularityTopology<GModel_Surface> Cad_gSingularityTopology;
}

#endif // !_Cad_gSingularityTopologyFwd_Header
