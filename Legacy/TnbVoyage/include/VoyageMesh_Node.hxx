#pragma once
#ifndef _VoyageMesh_Node_Header
#define _VoyageMesh_Node_Header

#include <Pnt2d.hxx>
#include <Global_Indexed.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/7/2023 Payvand]

	class VoyageMesh_Edge;
	class VoyageMesh_Element;

	class VoyageMesh_Node
		: public Global_Indexed
	{

		/*Private Data*/

		Pnt2d theCoord_;


		std::map<Standard_Integer, std::weak_ptr<VoyageMesh_Edge>> theEdges_;
		std::map<Standard_Integer, std::weak_ptr<VoyageMesh_Element>> theElements_;

	public:

		// default constructor [8/7/2023 Payvand]

		VoyageMesh_Node()
		{}

		// constructors [8/7/2023 Payvand]

		VoyageMesh_Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
			: Global_Indexed(theIndex)
			, theCoord_(theCoord)
		{}

		VoyageMesh_Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
			: Global_Indexed(theIndex)
			, theCoord_(std::move(theCoord))
		{}


		// Public functions and operators [8/7/2023 Payvand]

		virtual Standard_Boolean IsBoundary() const { return Standard_False; }

		const auto& Coord() const { return theCoord_; }

		const auto& Edges() const { return theEdges_; }
		const auto& Elements() const { return theElements_; }

		void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
		void SetCoord(Pnt2d&& theCoord) { theCoord_ = std::move(theCoord); }

		void ImportEdge(const Standard_Integer theIndex, const std::shared_ptr<VoyageMesh_Edge>& theEdge);
		void ImportElement(const Standard_Integer theIndex, const std::shared_ptr<VoyageMesh_Element>& theElement);

	};
}

#endif // !_VoyageMesh_Node_Header
