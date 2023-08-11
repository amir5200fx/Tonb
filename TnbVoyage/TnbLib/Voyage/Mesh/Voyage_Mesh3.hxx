#pragma once
#ifndef _Voyage_Mesh3_Header
#define _Voyage_Mesh3_Header

#include <VoyageMesh_Core.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageMesh_Element;
	class VoyageMesh_Edge;
	class VoyageMesh_Node;
	class Voyage_Path3;

	template<class T>
	class Geo_AdTree;

	class Voyage_Mesh3
		: public VoyageMesh_Core
		, public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Voyage_Path3> theRefPath_;

		std::vector<std::shared_ptr<VoyageMesh_Edge>> theProtPath_;
		std::vector<std::shared_ptr<VoyageMesh_Edge>> theStarboardPath_;

		//- the searching engine
		std::shared_ptr<Geo_AdTree<std::shared_ptr<VoyageMesh_Node>>> theEngine_;

		//- Results

		std::vector<std::shared_ptr<VoyageMesh_Element>> thePort_;
		std::vector<std::shared_ptr<VoyageMesh_Element>> theStarboard_;

		//- Private functions and operators

		void MeshOneLevel();
		void FindValidNode(const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theCandidates, const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theEdges);
		void Update();

		/*Standard_Boolean GetEntity();
		Standard_Boolean IsBelongToFront() const;

		void CalcElementSize() const;
		void CalcOptCoord();
		void CalcLocalFrontRadius();

		void RetrieveLocalFrontNodes(std::vector<std::shared_ptr<VoyageMesh_Node>>& theLocals, std::vector<std::shared_ptr<VoyageMesh_Node>>& theCandidates) const;
		void RetrieveLocalFrontEntities(const std::vector<std::shared_ptr<VoyageMesh_Node>>&, std::vector<std::shared_ptr<VoyageMesh_Edge>>&) const;
		void SortNodes(std::vector<std::shared_ptr<VoyageMesh_Node>>&) const;
		void AddOptNodeTo(std::vector<std::shared_ptr<VoyageMesh_Node>>&) const;

		Standard_Boolean IsNewPointCandidate(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&) const;

		void FindValidPoint(const std::vector<std::shared_ptr<VoyageMesh_Node>>&, const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);
		void Update();

		void NextLevel(const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges);*/

	public:

		//- default constructor

		Voyage_Mesh3()
		{}

		//- constructors

		//- Public functions and operators

		const auto& RefPath() const { return theRefPath_; }

		const auto& Port() const { return thePort_; }
		const auto& Starboard() const { return theStarboard_; }

		void Perform();

		void SetRefPath(const std::shared_ptr<Voyage_Path3>& thePath) { theRefPath_ = thePath; }
		void SetRefPath(std::shared_ptr<Voyage_Path3>&& thePath) { theRefPath_ = std::move(thePath); }

	};
}

#endif // !_Voyage_Mesh3_Header
