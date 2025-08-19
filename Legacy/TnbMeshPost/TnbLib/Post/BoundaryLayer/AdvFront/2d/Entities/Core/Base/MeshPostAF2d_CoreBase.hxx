#pragma once
#ifndef _MeshPostAF2d_CoreBase_Header
#define _MeshPostAF2d_CoreBase_Header

#include <MeshPostAF2d_CoreBaseFwd.hxx>
#include <MeshPostAF2d_FrontGlobalData.hxx>
#include <MeshPostAF2d_GlobalData.hxx>
#include <MeshPostAF2d_FrontInfo.hxx>
#include <MeshPostAF2d_Edge.hxx>
#include <MeshPost_Module.hxx>
#include <Aft_Core_Base.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Geo2d_SizeFun.hxx>

namespace tnbLib
{

	template<>
	TnbMeshPost_EXPORT void MeshPostAF2d_CoreBase::AddOptimumNodeTo
	(
		std::vector<std::shared_ptr<MeshPostAF2d_Node>>&
	);

	template<>
	template<>
	TnbMeshPost_EXPORT void MeshPostAF2d_CoreBase::RetrieveLocalFrontEntities<void>
		(
			const std::vector<std::shared_ptr<MeshPostAF2d_Node>>& theNodes,
			std::vector<std::shared_ptr<MeshPostAF2d_Edge>>& theEdges
		) const;
}

#endif // !_MeshPostAF2d_CoreBase_Header
