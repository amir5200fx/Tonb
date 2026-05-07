#pragma once
namespace tnbLib
{

	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurface::Import
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundary,
		const std::shared_ptr<Aft2d_MetricPrcsrSurface>& theBoundaryMap
	);

	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurface::FindValidNode
	(
		const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theCandidates,
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theEdges
	);

#ifdef AFT_MODEL_DEBUG
	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurface::MeshingOneLevel();
#endif // AFT_MODEL_DEBUG


	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurface::InsertNewFrontsToLevels();

	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurface::CompactNumbering
	(
		const std::vector<std::shared_ptr<Aft2d_ElementSurface>>& theElements
	) const;

	template<>
	void TnbMesh_EXPORT Aft2d_gModelSurface::CheckSelfIntersection();

	template<>
	static TnbMesh_EXPORT void Aft2d_gModelSurface::ActiveFront
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theFronts
	);

	template<>
	static TnbMesh_EXPORT void Aft2d_gModelSurface::CheckBoundary
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theFronts
	);

}