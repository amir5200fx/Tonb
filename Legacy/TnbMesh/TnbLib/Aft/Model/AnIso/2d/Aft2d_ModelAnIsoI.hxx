#pragma once
namespace tnbLib
{

	template<>
	void TnbMesh_EXPORT Aft2d_ModelAnIso::Import
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>& theBoundary,
		const std::shared_ptr<Aft2d_MetricPrcsrAnIso>& theBoundaryMap
	);

	template<>
	void TnbMesh_EXPORT Aft2d_ModelAnIso::FindValidNode
	(
		const std::vector<std::shared_ptr<Aft2d_NodeAnIso>>& theCandidates,
		const std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>& theEdges
	);

#ifdef AFT_MODEL_DEBUG
	template<>
	void TnbMesh_EXPORT Aft2d_ModelAnIso::MeshingOneLevel();
#endif // AFT_MODEL_DEBUG


	template<>
	void TnbMesh_EXPORT Aft2d_ModelAnIso::InsertNewFrontsToLevels();

	template<>
	void TnbMesh_EXPORT Aft2d_ModelAnIso::CompactNumbering
	(
		const std::vector<std::shared_ptr<Aft2d_ElementAnIso>>& theElements
	) const;

	template<>
	static TnbMesh_EXPORT void Aft2d_ModelAnIso::ActiveFront
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>& theFronts
	);

	template<>
	static TnbMesh_EXPORT void Aft2d_ModelAnIso::CheckBoundary
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>& theFronts
	);

}