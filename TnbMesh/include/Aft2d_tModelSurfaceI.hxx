#pragma once
namespace tnbLib
{

	template<>
	void TnbMesh_EXPORT Aft2d_tModelSurface::Import
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundary,
		const std::shared_ptr<Aft2d_MetricPrcsrSurface>& theBoundaryMap
	);

	template<>
	void TnbMesh_EXPORT Aft2d_tModelSurface::FindValidNode
	(
		const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theCandidates,
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theEdges
	);

#ifdef AFT_MODEL_DEBUG
	template<>
	void TnbMesh_EXPORT Aft2d_tModelSurface::MeshingOneLevel();
#endif // AFT_MODEL_DEBUG


	template<>
	void TnbMesh_EXPORT Aft2d_tModelSurface::InsertNewFrontsToLevels();

	template<>
	void TnbMesh_EXPORT Aft2d_tModelSurface::CompactNumbering
	(
		const std::vector<std::shared_ptr<Aft2d_ElementSurface>>& theElements
	) const;

	template<>
	static TnbMesh_EXPORT void Aft2d_tModelSurface::ActiveFront
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theFronts
	);

	template<>
	static TnbMesh_EXPORT void Aft2d_tModelSurface::CheckBoundary
	(
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theFronts
	);

}