#pragma once
#ifndef _VoyageMesh_CoreBase_Header
#define _VoyageMesh_CoreBase_Header

#include <VoyageMesh_CoreBaseFwd.hxx>
#include <VoyageMesh_FrontGlobalData.hxx>
#include <VoyageMesh_GlobalData.hxx>
#include <VoyageMesh_FrontInfo.hxx>
#include <VoyageMesh_Edge.hxx>
#include <Voyage_Module.hxx>
#include <Aft_Core_Base.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Geo2d_SizeFun.hxx>

namespace tnbLib
{

	template<>
	TnbVoyage_EXPORT Standard_Boolean VoyageMesh_CoreBase::IsSameLevelFueled();
	template<>
	TnbVoyage_EXPORT Standard_Boolean VoyageMesh_CoreBase::IsCavityRemoverFueled();

	template<>
	TnbVoyage_EXPORT void VoyageMesh_CoreBase::AddOptimumNodeTo
	(
		std::vector<std::shared_ptr<VoyageMesh_Node>>&
	);

	template<>
	template<>
	TnbVoyage_EXPORT void VoyageMesh_CoreBase::RetrieveLocalFrontEntities<void>
		(
			const std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes,
			std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
		) const;

	template<>
	TnbVoyage_EXPORT void VoyageMesh_CoreBase::CalcElementSize();

	template<>
	TnbVoyage_EXPORT void VoyageMesh_CoreBase::CalcLocalFrontRadius();
}

#endif // !_VoyageMesh_CoreBase_Header
