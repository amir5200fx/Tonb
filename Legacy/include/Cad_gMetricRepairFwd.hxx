#pragma once
#ifndef _Cad_gMetricRepairFwd_Header
#define _Cad_gMetricRepairFwd_Header

namespace tnbLib
{

	// Forward Declarations [6/6/2022 Amir]
	template<class SurfType>
	class Cad_MetricRepair;

	class GModel_Surface;

	typedef Cad_MetricRepair<GModel_Surface> Cad_gMetricRepair;
}

#endif // !_Cad_gMetricRepairFwd_Header
