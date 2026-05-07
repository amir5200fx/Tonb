#pragma once
namespace tnbLib
{

	template<>
	void TnbMesh_EXPORT Aft2d_Model::Import
	(
		const std::vector<std::shared_ptr<Aft2d_Edge>>& theBoundary,
		const std::shared_ptr<Aft2d_MetricPrcsr>& theBoundaryMap
	);

	template<>
	void TnbMesh_EXPORT Aft2d_Model::FindValidNode
	(
		const std::vector<std::shared_ptr<Aft2d_Node>>& theCandidates, 
		const std::vector<std::shared_ptr<Aft2d_Edge>>& theEdges
	);

#ifdef AFT_MODEL_DEBUG
	template<>
	void TnbMesh_EXPORT Aft2d_Model::MeshingOneLevel();
#endif // AFT_MODEL_DEBUG


	template<>
	void TnbMesh_EXPORT Aft2d_Model::InsertNewFrontsToLevels();

	template<>
	void TnbMesh_EXPORT Aft2d_Model::CompactNumbering
	(
		const std::vector<std::shared_ptr<Aft2d_Element>>& theElements
	) const;

	template<>
	static TnbMesh_EXPORT void Aft2d_Model::ActiveFront
	(
		const std::vector<std::shared_ptr<Aft2d_Edge>>& theFronts
	);

	template<>
	static TnbMesh_EXPORT void Aft2d_Model::CheckBoundary
	(
		const std::vector<std::shared_ptr<Aft2d_Edge>>& theFronts
	);

}