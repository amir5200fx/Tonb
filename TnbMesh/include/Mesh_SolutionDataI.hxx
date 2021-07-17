#pragma once
template<class GeomType>
inline tnbLib::Mesh_SolutionData<GeomType>::Mesh_SolutionData
(
	const std::shared_ptr<GeomType>& theGeometry,
	const std::shared_ptr<Mesh_ReferenceValues>& theReferences
)
	: theGeometry_(theGeometry)
	, theReferences_(theReferences)
{
	// empty body [4/5/2021 Amir]
}