#pragma once
#ifndef _GeoMesh2d_MetricBackground_Header
#define _GeoMesh2d_MetricBackground_Header

#include <Entity2d_Metric1.hxx>
#include <GeoMesh2d_Data.hxx>
#include <GeoMesh_Background.hxx>
#include <GeoMesh2d_MetricBackgroundFwd.hxx>

namespace tnbLib
{

	template<>
	void GeoMesh2d_MetricBackground::ConnectTopology();

	template<>
	void GeoMesh2d_MetricBackground::HvCorrection
	(
		const std::vector<std::shared_ptr<Mesh2d_Node>>& nodes,
		const Standard_Real Factor,
		const Standard_Integer MaxInnerIteration
	);

	template<>
	void GeoMesh2d_MetricBackground::ExportToPlt(OFstream& File) const;
}

#endif // !_GeoMesh2d_MetricBackground_Header