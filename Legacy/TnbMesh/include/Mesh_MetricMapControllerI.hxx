#pragma once
template<class GeomType>
inline tnbLib::Mesh_MetricMapController<GeomType>::Mesh_MetricMapController
(
	const std::shared_ptr<GeomType>& theGeometry,
	const std::shared_ptr<Mesh_ReferenceValues>& theReferences
)
	: theGeometry_(theGeometry)
	, theReferences_(theReferences)
{
	// empty body [11/26/2021 Amir]
}