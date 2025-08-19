#pragma once
#ifndef _Mesh2d_PlnWireUniMetricFwd_Header
#define _Mesh2d_PlnWireUniMetricFwd_Header

#include <Mesh2d_PlnCurveUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/12/2022 Amir]
	template<class MeshPlnCurve>
	class Mesh_PlnWire;

	typedef Mesh_PlnWire<Mesh2d_PlnCurveUniMetric> Mesh2d_PlnWireUniMetric;
}

#endif // !_Mesh2d_PlnWireUniMetricFwd_Header
