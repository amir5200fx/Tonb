#pragma once
#ifndef _MeshPost2d_BoundaryLayer_Header
#define _MeshPost2d_BoundaryLayer_Header

#include <MeshPost_Module.hxx>
#include <Pnt2d.hxx>
#include <Global_Indexed.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <map>

#include "MeshPost2d_BoundaryLayer.hxx"

namespace tnbLib
{

	class MeshPost2d_BoundaryLayer
		: public Global_Done
	{

	public:

		// Forward Declarations
		class Edge2d;
		class Element2d;

		class Node2dAdaptor
		{
			/*Private Data*/
			std::map<Standard_Integer, std::weak_ptr<Element2d>> theElements_;
			std::map<Standard_Integer, std::weak_ptr<Edge2d>> theEdges_;
		protected:
			// Default constructor
			Node2dAdaptor() = default;
			// Constructors
		public:
			// Public functions and operators
			const auto& Elements() const { return theElements_; }
			const auto& Edges() const { return theEdges_; }

			Standard_Integer NbEdges() const;
			Standard_Integer NbElements() const;

			void ImportElement(const Standard_Integer theIndex, const std::shared_ptr<Element2d>&);
			void ImportEdge(const Standard_Integer theIndex, const std::shared_ptr<Edge2d>&);
		};

		class Node2d
			: public Global_Indexed
			, public Node2dAdaptor
		{
			/*Private Data*/
			Pnt2d theCoord_;
		protected:
			// default constructor
			Node() = default;
			// constructors
			Node(Standard_Integer theIndex, Pnt2d theCoord);
		public:
			// Public functions and operators
			const auto& Coords() const { return theCoord_; }

			void SetCoords(Pnt2d theCoords);
		};

		class BoundaryNode2d
			: public Node2d
		{
			/*Private Data*/
		public:
			// default constructor
			BoundaryNode() = default;
			// constructors
			BoundaryNode(Standard_Integer theIndex, Pnt2d thePnt);
		};

		class InteriorNode2d
			: public Node2d
		{
			/*Private Data*/
		public:
			// default constructor
			InteriorNode() = default;
			// constructors
			InteriorNode(Standard_Integer theIndex, Pnt2d thePnt);
		};

		class Edge2d
			: public Global_Indexed
		{
		public:
			enum  { nb_nodes = 2 };
			typedef std::array<std::shared_ptr<Node2d>, nb_nodes> Array2;
		private:
			/*Private Data*/
			Array2 theNodes_;
		protected:
			// default constructor
			Edge2d() = default;
			// constructors
			Edge2d(Standard_Integer theIndex, Array2 theNodes);
		public:
			// Public functions and operators
			const auto& Nodes() const { return theNodes_; }
			const auto& Node0() const { return std::get<0>(theNodes_); }
			const auto& Node1() const { return std::get<1>(theNodes_); }

			void SetNodes(Array2 theNodes);
		};

		class BoundaryEdge2dAdaptor
		{
			/*Private Data*/
			std::weak_ptr<Element2d> theElement_;
		protected:
			// default constructor
			BoundaryEdge2dAdaptor() = default;
		public:
			// Public functions and operators
			const auto& Element() const { return theElement_; }

			void SetElement(const std::shared_ptr<Element2d>&);
		};
		class BoundaryEdge2d
			: public Edge2d
			, public BoundaryEdge2dAdaptor
		{
			/*Private Data*/
		public:
			// default constructor
			BoundaryEdge2d() = default;
			// constructors
			BoundaryEdge2d(Standard_Integer theIndex, Array2 theNodes);
		};

	private:

		/*Private Data*/

	public:

		// default constructors [6/22/2023 Payvand]

		MeshPost2d_BoundaryLayer()
		{}

	};
}

#endif // !_MeshPost2d_BoundaryLayer_Header
