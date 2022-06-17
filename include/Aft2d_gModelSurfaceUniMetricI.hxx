#pragma once
namespace tnbLib
{

	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurfaceUniMetric::Import
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundary,
		const std::shared_ptr<Aft2d_MetricPrcsrSurfaceUniMetric>& theBoundaryMap
	);

	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurfaceUniMetric::FindValidNode
	(
		const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theCandidates,
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theEdges
	);

#ifdef AFT_MODEL_DEBUG
	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurfaceUniMetric::MeshingOneLevel();
#endif // AFT_MODEL_DEBUG


	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurfaceUniMetric::InsertNewFrontsToLevels();

	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurfaceUniMetric::CompactNumbering
	(
		const std::vector<std::shared_ptr<Aft2d_ElementSurface>>& theElements
	) const;

	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurfaceUniMetric::CheckSelfIntersection();

	template<>
	static TnbMesh_EXPORT void Aft2d_gModelSurfaceUniMetric::ActiveFront
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theFronts
	);

	template<>
	static TnbMesh_EXPORT void Aft2d_gModelSurfaceUniMetric::CheckBoundary
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theFronts
	);

}