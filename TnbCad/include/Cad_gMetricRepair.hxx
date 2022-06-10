#pragma once
#ifndef _Cad_gMetricRepair_Header
#define _Cad_gMetricRepair_Header

#include <Cad_MetricRepair.hxx>
#include <Cad_gMetricRepairFwd.hxx>

namespace tnbLib
{

	template<>
	TnbCad_EXPORT void Cad_gMetricRepair::Perform();
}

#endif // !_Cad_gMetricRepair_Header
