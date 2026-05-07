#pragma once
namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft3d_Model::Import
	(
		const std::vector<std::shared_ptr<Aft3d_Facet>>& theBoundaries, 
		const std::shared_ptr<Aft3d_MetricPrcsr>& theBoundaryMap
	);

	template<>
	TnbMesh_EXPORT void Aft3d_Model::FindValidNode
	(
		const std::vector<std::shared_ptr<Aft3d_Node>>& theCandidates,
		const std::vector<std::shared_ptr<Aft3d_Facet>>& theFacets
	);

	template<>
	void Aft3d_Model::InsertNewFrontsToLevels();

	template<>
	TnbMesh_EXPORT void Aft3d_Model::CompactNumbering
	(
		const std::vector<std::shared_ptr<Aft3d_Element>>& theElements
	) const;

	template<>
	TnbMesh_EXPORT void Aft3d_Model::ActiveFront
	(
		const std::vector<std::shared_ptr<Aft3d_Facet>>& theFronts
	);

	template<>
	TnbMesh_EXPORT void Aft3d_Model::CheckBoundary
	(
		const std::vector<std::shared_ptr<Aft3d_Facet>>& theFronts
	);

}