#pragma once
namespace tnbLib
{

	template<>
	void TnbMesh_EXPORT Aft2d_tModelSurfaceUniMetric::Import
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundary,
		const std::shared_ptr<Aft2d_MetricPrcsrSurfaceUniMetric>& theBoundaryMap
	);

	template<>
	void TnbMesh_EXPORT Aft2d_tModelSurfaceUniMetric::FindValidNode
	(
		const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theCandidates,
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theEdges
	);

#ifdef AFT_MODEL_DEBUG
	template<>
	void TnbMesh_EXPORT Aft2d_tModelSurfaceUniMetric::MeshingOneLevel();
#endif // AFT_MODEL_DEBUG


	template<>
	void TnbMesh_EXPORT Aft2d_tModelSurfaceUniMetric::InsertNewFrontsToLevels();

	template<>
	void TnbMesh_EXPORT Aft2d_tModelSurfaceUniMetric::CompactNumbering
	(
		const std::vector<std::shared_ptr<Aft2d_ElementSurface>>& theElements
	) const;

	template<>
	static TnbMesh_EXPORT void Aft2d_tModelSurfaceUniMetric::ActiveFront
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theFronts
	);

	template<>
	static TnbMesh_EXPORT void Aft2d_tModelSurfaceUniMetric::CheckBoundary
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theFronts
	);

}