#pragma once
#ifndef _Voyage_Mesh3_Header
#define _Voyage_Mesh3_Header

#include <VoyageMesh_Core.hxx>
#include <Voyage_Module.hxx>
#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>
#include <Aft_Model_Constants.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageMesh_RefEdge;
	class VoyageMesh_Element;
	class VoyageMesh_Edge;
	class VoyageMesh_Node;
	class Voyage_Path3;

	template<class T>
	class Geo_AdTree;

	class Voyage_Mesh
		: public VoyageMesh_Core
		, public Aft_Model_Constants
		, public Global_Done
	{

		/*Private Data*/

		//std::shared_ptr<Voyage_Path3> theRefPath_;
		std::vector<std::shared_ptr<VoyageMesh_Edge>> theRefPath_;

		//- Results

		//- Private functions and operators

		TnbVoyage_EXPORT void MeshOneLevel();
		TnbVoyage_EXPORT void FindValidNode
		(
			const std::vector<std::shared_ptr<VoyageMesh_Node>>& theCandidates, 
			const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
		);
		TnbVoyage_EXPORT void Update();
		TnbVoyage_EXPORT void Mesh();

		TnbVoyage_EXPORT void InsertNewFrontsToLevels();
		TnbVoyage_EXPORT void CheckPath(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&) const;
		TnbVoyage_EXPORT void CheckSelfIntersection() const;

		TnbVoyage_EXPORT void Import
		(
			const std::vector<std::shared_ptr<VoyageMesh_Edge>>& thePath,
			const std::shared_ptr<VoyageMesh_MetricPrcsr>& theMetrics
		);

		static TnbVoyage_EXPORT void ActiveFronts
		(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);

	public:

		//- default constructor

		Voyage_Mesh()
		{}

		//- constructors

		//- Public functions and operators

		const auto& RefPath() const { return theRefPath_; }

		TnbVoyage_EXPORT void Perform();

		//void SetRefPath(const std::shared_ptr<Voyage_Path3>& thePath) { theRefPath_ = thePath; }
		//void SetRefPath(std::shared_ptr<Voyage_Path3>&& thePath) { theRefPath_ = std::move(thePath); }

		TnbVoyage_EXPORT void LoadRefPath(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);
		TnbVoyage_EXPORT void LoadRefPath(std::vector<std::shared_ptr<VoyageMesh_Edge>>&&);

		static TnbVoyage_EXPORT std::vector<std::shared_ptr<VoyageMesh_Node>> 
			RetrieveNodesFrom
			(
				const std::vector<std::shared_ptr<VoyageMesh_Edge>>&
			);
		static TnbVoyage_EXPORT Entity2d_Box
			RetrieveBoundingBox
			(
				const std::vector<std::shared_ptr<VoyageMesh_Node>>&
			);

		static TnbVoyage_EXPORT Standard_Real Length(const std::shared_ptr<VoyageMesh_Edge>&);
		static TnbVoyage_EXPORT const Pnt2d& GetCoord(const std::shared_ptr<VoyageMesh_Node>&);
	};
}

#endif // !_Voyage_Mesh3_Header
