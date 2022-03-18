#pragma once
namespace tnbLib
{

	template<>
	void TnbMesh_EXPORT Aft2d_ModelUniMetric::Import
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>& theBoundary,
		const std::shared_ptr<Aft2d_MetricPrcsrUniMetric>& theBoundaryMap
	);

	template<>
	void TnbMesh_EXPORT Aft2d_ModelUniMetric::FindValidNode
	(
		const std::vector<std::shared_ptr<Aft2d_NodeAnIso>>& theCandidates,
		const std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>& theEdges
	);

#ifdef AFT_MODEL_DEBUG
	template<>
	void TnbMesh_EXPORT Aft2d_ModelUniMetric::MeshingOneLevel();
#endif // AFT_MODEL_DEBUG


	template<>
	void TnbMesh_EXPORT Aft2d_ModelUniMetric::InsertNewFrontsToLevels();

	template<>
	void TnbMesh_EXPORT Aft2d_ModelUniMetric::CompactNumbering
	(
		const std::vector<std::shared_ptr<Aft2d_ElementAnIso>>& theElements
	) const;

	template<>
	static TnbMesh_EXPORT void Aft2d_ModelUniMetric::ActiveFront
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>& theFronts
	);

	template<>
	static TnbMesh_EXPORT void Aft2d_ModelUniMetric::CheckBoundary
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>& theFronts
	);

}