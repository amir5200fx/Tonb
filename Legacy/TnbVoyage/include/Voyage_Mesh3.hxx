#pragma once
#ifndef _Voyage_Mesh3_Header
#define _Voyage_Mesh3_Header

#include <VoyageMesh_Core.hxx>
#include <Voyage_Module.hxx>
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

		TnbVoyage_EXPORT void MeshOneLevel();
		TnbVoyage_EXPORT void FindValidNode
		(
			const std::vector<std::shared_ptr<VoyageMesh_Node>>& theCandidates, 
			const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
		);
		TnbVoyage_EXPORT void Update();

		TnbVoyage_EXPORT void InsertNewFrontsToLevels();

	public:

		//- default constructor

		Voyage_Mesh3()
		{}

		//- constructors

		//- Public functions and operators

		const auto& RefPath() const { return theRefPath_; }

		const auto& Port() const { return thePort_; }
		const auto& Starboard() const { return theStarboard_; }

		TnbVoyage_EXPORT void Perform();

		void SetRefPath(const std::shared_ptr<Voyage_Path3>& thePath) { theRefPath_ = thePath; }
		void SetRefPath(std::shared_ptr<Voyage_Path3>&& thePath) { theRefPath_ = std::move(thePath); }

		static TnbVoyage_EXPORT std::vector<std::shared_ptr<VoyageMesh_Node>> 
			RetrieveNodesFrom
			(
				const std::vector<std::shared_ptr<VoyageMesh_Edge>>&
			);
	};
}

#endif // !_Voyage_Mesh3_Header
