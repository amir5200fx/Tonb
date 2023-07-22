#pragma once
#ifndef _GeoMesh2d_MetricBackground_Header
#define _GeoMesh2d_MetricBackground_Header

#include <Entity2d_Metric1.hxx>
#include <GeoMesh2d_Data.hxx>
#include <GeoMesh_Background.hxx>
#include <GeoMesh2d_MetricBackgroundFwd.hxx>
#include <GeoMesh2d_SingleMetricBackgroundFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void GeoMesh2d_SingleMetricBackground::ConnectTopology();

	template<>
	TnbMesh_EXPORT void GeoMesh2d_SingleMetricBackground::HvCorrection
	(
		const std::vector<std::shared_ptr<Mesh2d_Node>>& nodes,
		const Standard_Real Factor,
		const Standard_Integer MaxInnerIteration
	);

	template<>
	TnbMesh_EXPORT void GeoMesh2d_SingleMetricBackground::ExportToPlt(OFstream& File) const;
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoMesh2d_MetricBackground);
BOOST_CLASS_EXPORT_KEY(tnbLib::GeoMesh2d_SingleMetricBackground);

#endif // !_GeoMesh2d_MetricBackground_Header