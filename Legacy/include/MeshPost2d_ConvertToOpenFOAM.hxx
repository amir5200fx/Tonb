#pragma once
#ifndef _MeshPost2d_ConvertToOpenFOAM_Header
#define _MeshPost2d_ConvertToOpenFOAM_Header

#include <MeshPost_Module.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity_Connectivity.hxx>
#include <Pnt3d.hxx>
#include <Pnt2d.hxx>
#include <Global_Indexed.hxx>
#include <Global_Done.hxx>

#include <map>
#include <set>
#include <vector>
#include <array>

//#include <dictionary.hxx>

namespace tnbLib
{

	// Forward Declarations [7/6/2023 Payvand]
	class MeshPost2d_OFTopology;

	class MeshPost2d_ConvertToOpenFOAM
		: public Global_Done
	{

	public:

		class PointList
		{

			/*Private Data*/

			std::vector<Pnt3d> theCoords_;

		public:

			// default constructor [6/27/2023 Payvand]

			PointList()
			{}

			// constructors [6/27/2023 Payvand]

			PointList(const std::vector<Pnt3d>& theCoords)
				: theCoords_(theCoords)
			{}

			PointList(std::vector<Pnt3d>&& theCoords)
				: theCoords_(std::move(theCoords))
			{}


			// Public functions and operators [6/27/2023 Payvand]

			const auto& Coords() const { return theCoords_; }
			auto& CoordsRef() { return theCoords_; }

			friend TnbMeshPost_EXPORT Ostream& operator<<(Ostream& os, const PointList&);
		};

		class Face
		{

			/*Private Data*/

			std::vector<Standard_Integer> theNodes_;

		public:

			// default constructor [6/27/2023 Payvand]

			Face()
			{}

			// constructors [6/27/2023 Payvand]

			Face(const std::vector<Standard_Integer>& theNodes)
				: theNodes_(theNodes)
			{}

			Face(std::vector<Standard_Integer>&& theNodes)
				: theNodes_(std::move(theNodes))
			{}

			// Public functions and operators [6/27/2023 Payvand]

			const auto& Nodes() const { return theNodes_; }
			auto& NodesRef() { return theNodes_; }

		};

		class FaceList
		{

			/*Private Data*/

			std::vector<Face> theFaces_;

		public:

			// default constructor [6/27/2023 Payvand]

			FaceList()
			{}

			// Constructors [6/27/2023 Payvand]

			FaceList(const std::vector<Face>& theFaces)
				: theFaces_(theFaces)
			{}

			FaceList(std::vector<Face>&& theFaces)
				: theFaces_(std::move(theFaces))
			{}

			// Public functions and operators [6/27/2023 Payvand]

			const auto& Faces() const { return theFaces_; }
			auto& FacesRef() { return theFaces_; }

			friend TnbMeshPost_EXPORT Ostream& operator<<(Ostream& os, const FaceList&);

		};

		class Cell
		{

		public:

			enum
			{
				nbFaces = 5
			};

		private:

			// Private Data [6/27/2023 Payvand]

			std::array<Standard_Integer, nbFaces> theFaces_;

		public:

			// default constructor [6/27/2023 Payvand]

			Cell()
			{}

			// constructors [6/27/2023 Payvand]

			Cell(const std::array<Standard_Integer, nbFaces>& theFaces)
				: theFaces_(theFaces)
			{}

			Cell(std::array<Standard_Integer, nbFaces>&& theFaces)
				: theFaces_(std::move(theFaces))
			{}


			// Public functions and operators [6/27/2023 Payvand]

			const auto& Faces() const { return theFaces_; }
			auto& FacesRef() { return theFaces_; }

		};

		class CellList
		{

			/*Private Data*/

			std::vector<Cell> theCells_;

		public:

			// default constructor [6/27/2023 Payvand]

			CellList()
			{}

			// constructors [6/27/2023 Payvand]

			CellList(const std::vector<Cell>& theCells)
				: theCells_(theCells)
			{}

			CellList(std::vector<Cell>&& theCells)
				: theCells_(std::move(theCells))
			{}


			// Public functions and operators [6/27/2023 Payvand]

			const auto& Cells() const { return theCells_; }
			auto& CellsRef() { return theCells_; }

			friend TnbMeshPost_EXPORT Ostream& operator<<(Ostream& os, const CellList&);

		};

		class OwnerList
		{

			/*Private Data*/

			std::vector<Standard_Integer> theOwners_;

		public:

			// default constructor [6/27/2023 Payvand]

			OwnerList()
			{}

			// constructors [6/27/2023 Payvand]

			OwnerList(const std::vector<Standard_Integer>& theOwners)
				: theOwners_(theOwners)
			{}

			OwnerList(std::vector<Standard_Integer>&& theOwners)
				: theOwners_(std::move(theOwners))
			{}


			// Public functions and operators [6/27/2023 Payvand]

			const auto& Owners() const { return theOwners_; }
			auto& Owners() { return theOwners_; }

			friend TnbMeshPost_EXPORT Ostream& operator<<(Ostream& os, const OwnerList&);

		};

		class NeighborList
		{

			/*Private Data*/

			std::vector<Standard_Integer> theNeighbors_;

		public:

			// default constructor [6/27/2023 Payvand]

			NeighborList()
			{}

			// constructors [6/27/2023 Payvand]

			NeighborList(const std::vector<Standard_Integer>& theNeighbors)
				: theNeighbors_(theNeighbors)
			{}

			NeighborList(std::vector<Standard_Integer>&& theNeighbors)
				: theNeighbors_(std::move(theNeighbors))
			{}


			// Public functions and operators [6/27/2023 Payvand]

			const auto& Neighbors() const { return theNeighbors_; }
			auto& NeighborsRef() { return theNeighbors_; }

			friend TnbMeshPost_EXPORT Ostream& operator<<(Ostream& os, const NeighborList&);

		};

		class Facet;
		class Element;

		class Node
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt3d theCoord_;

		protected:

			// default constructor [6/27/2023 Payvand]

			Node()
			{}

			// constructors [6/27/2023 Payvand]

			Node(const Standard_Integer theIndex, const Pnt3d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
			{}

			Node(const Standard_Integer theIndex, Pnt3d&& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(std::move(theCoord))
			{}

		public:

			// Public functions and operators [6/27/2023 Payvand]

			virtual ~Node(){}

			const auto& Coord() const { return theCoord_; }
			auto& CoordRef() { return theCoord_; }

		};

		class SlaveNode;

		class MasterNode
			: public Node
		{

			/*Private Data*/

			std::shared_ptr<SlaveNode> theSlave_;

		public:

			// default constructor [6/27/2023 Payvand]

			MasterNode()
			{}

			// constructors [6/27/2023 Payvand]

			MasterNode(const Standard_Integer theIndex, const Pnt3d& theCoord)
				: Node(theIndex, theCoord)
			{}

			MasterNode(const Standard_Integer theIndex, Pnt3d&& theCoord)
				: Node(theIndex, std::move(theCoord))
			{}

			// Public functions and operators [6/27/2023 Payvand]

			const auto& Slave() const
			{
				return theSlave_;
			}

			auto& SlaveRef() { return theSlave_; }

		};

		class SlaveNode
			: public Node
		{

			/*Private Data*/

		public:

			// default constructor [6/27/2023 Payvand]

			SlaveNode()
			{}

			// constructors [6/27/2023 Payvand]

			SlaveNode(const Standard_Integer theIndex, const Pnt3d& theCoord)
				: Node(theIndex, theCoord)
			{}

			SlaveNode(const Standard_Integer theIndex, Pnt3d&& theCoord)
				: Node(theIndex, std::move(theCoord))
			{}


		};

		class Facet
			: public Global_Indexed
		{

			/*Private Data*/

		protected:

			// default constructor [6/27/2023 Payvand]

			Facet()
			{}

			Facet(const Standard_Integer theIndex)
				: Global_Indexed(theIndex)
			{}

		public:

			// Public functions and operators [6/27/2023 Payvand]

			virtual Standard_Integer NbNodes() const = 0;

			virtual std::vector<std::shared_ptr<Node>> GetNodes() const = 0;

		};
		
		class TriFacet
			: public Facet
		{

		public:

			enum 
			{
				nbNodes = 3
			};

		private:

			/*Private Data*/

			std::array<std::shared_ptr<Node>, nbNodes> theNodes_;

		public:

			// default constructor [6/27/2023 Payvand]

			TriFacet()
			{}

			// constructors [6/27/2023 Payvand]

			TriFacet
			(
				const Standard_Integer theIndex,
				const std::array<std::shared_ptr<Node>, nbNodes>& theNodes
			)
				: Facet(theIndex)
				, theNodes_(theNodes)
			{}

			TriFacet
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Node>, nbNodes>&& theNodes
			)
				: Facet(theIndex)
				, theNodes_(std::move(theNodes))
			{}


			// Public functions and operators [6/27/2023 Payvand]

			const auto& Nodes() const { return theNodes_; }
			auto& NodesRef() { return theNodes_; }

			Standard_Integer NbNodes() const override { return (Standard_Integer)nbNodes; }
			TnbMeshPost_EXPORT std::vector<std::shared_ptr<Node>> GetNodes() const override;

		};

		class QuadFacet
			: public Facet
		{

		public:

			enum
			{
				nbNodes = 4
			};

		private:

			/*Private Data*/

			std::array<std::shared_ptr<Node>, nbNodes> theNodes_;

			std::weak_ptr<Element> theOwner_;
			std::weak_ptr<Element> theNeighbor_;

		public:

			// default constructor [6/27/2023 Payvand]

			QuadFacet()
			{}

			// constructors [6/27/2023 Payvand]

			QuadFacet
			(
				const Standard_Integer theIndex, 
				const std::array<std::shared_ptr<Node>, nbNodes>& theNodes
			)
				: Facet(theIndex)
				, theNodes_(theNodes)
			{}

			QuadFacet
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Node>, nbNodes>&& theNodes
			)
				: Facet(theIndex)
				, theNodes_(std::move(theNodes))
			{}


			// Public functions and operators [6/27/2023 Payvand]

			const auto& Nodes() const { return theNodes_; }
			auto& NodesRef() { return theNodes_; }

			Standard_Integer NbNodes() const override { return (Standard_Integer)nbNodes; }
			TnbMeshPost_EXPORT std::vector<std::shared_ptr<Node>> GetNodes() const override;

			const auto& Owner() const { return theOwner_; }
			const auto& Neighbor() const { return theNeighbor_; }

			void SetOwner(const std::weak_ptr<Element>& theElement) { theOwner_ = theElement; }
			void SetNeighbor(const std::weak_ptr<Element>& theElement) { theNeighbor_ = theElement; }

		};

		class Element
			: public Global_Indexed
		{

		public:

			enum 
			{
				nbFacets = 5
			};

		private:

			/*Private Data*/

			std::array<std::shared_ptr<Facet>, nbFacets> theFacets_;


		public:

			// default constructor [6/27/2023 Payvand]

			Element()
			{}

			// constructors [6/27/2023 Payvand]

			Element
			(
				const Standard_Integer theIndex, 
				const std::array<std::shared_ptr<Facet>, nbFacets>& theFacets
			)
				: Global_Indexed(theIndex)
				, theFacets_(theFacets)
			{}

			Element
			(
				const Standard_Integer theIndex, 
				std::array<std::shared_ptr<Facet>, nbFacets>&& theFacets
			)
				: Global_Indexed(theIndex)
				, theFacets_(std::move(theFacets))
			{}

			// Public functions and operators [6/27/2023 Payvand]

			const auto& Facets() const { return theFacets_; }
			auto& Facets() { return theFacets_; }

		};

		class Node2d
			: public Global_Indexed
		{

			/*Private Data*/

			std::shared_ptr<MasterNode> theNode_;

		public:

			// default constructor [6/28/2023 Payvand]

			Node2d()
			{}

			// constructors [6/28/2023 Payvand]

			Node2d
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<MasterNode>& theNode
			)
				: Global_Indexed(theIndex)
				, theNode_(theNode)
			{}

			Node2d
			(
				const Standard_Integer theIndex,
				std::shared_ptr<MasterNode>&& theNode
			)
				: Global_Indexed(theIndex)
				, theNode_(std::move(theNode))
			{}

			// Public functions and operators [6/28/2023 Payvand]

			const auto& Node3d() const { return theNode_; }
			auto& Node3dRef() { return theNode_; }

		};

		class Element2d;

		class Edge2d
			: public Global_Indexed
		{

		public:

			enum 
			{
				nbNodes = 2
			};

		private:

			/*Private Data*/

			std::array<std::shared_ptr<Node2d>, nbNodes> theNodes_;

			std::shared_ptr<QuadFacet> theExtruded_;

			std::weak_ptr<Element2d> theOwner_;
			std::weak_ptr<Element2d> theNeighbor_;

			//Standard_Boolean theSense_;

		public:

			// default constructor [6/28/2023 Payvand]

			Edge2d()
				/*: theSense_(Standard_True)*/
			{}

			// constructors [6/28/2023 Payvand]

			Edge2d
			(
				const Standard_Integer theIndex, 
				const std::array<std::shared_ptr<Node2d>, nbNodes>& theNodes
			)
				: Global_Indexed(theIndex)
				, theNodes_(theNodes)
				/*, theSense_(Standard_True)*/
			{}

			Edge2d
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Node2d>, nbNodes>&& theNodes
			)
				: Global_Indexed(theIndex)
				, theNodes_(std::move(theNodes))
				/*, theSense_(Standard_True)*/
			{}

			// Public functions and operators [6/28/2023 Payvand]

			//Standard_Boolean IsOnBoundary() const;
			//auto Sense() const { return theSense_; }

			const auto& Nodes() const { return theNodes_; }
			auto& NodesRef() { return theNodes_; }

			const auto& Extruded() const { return theExtruded_; }
			auto& ExtrudedRef() { return theExtruded_; }

			const auto& Owner() const { return theOwner_; }
			const auto& Neighbor() const { return theNeighbor_; }

			void SetOwner(const std::shared_ptr<Element2d>& theElement) { theOwner_ = theElement; }
			void SetNeighbor(const std::shared_ptr<Element2d>& theElement) { theNeighbor_ = theElement; }
			//void SetSense(const Standard_Boolean theSense) { theSense_ = theSense; }
		};

		class Element2d
			: public Global_Indexed
		{

		public:

			enum 
			{
				nbEdges = 3
			};

		private:

			/*Private Data*/

			std::array<std::shared_ptr<Edge2d>, nbEdges> theEdges_;

			std::shared_ptr<TriFacet> theBack_;
			std::shared_ptr<TriFacet> theFront_;

			std::shared_ptr<Element> theElement_;

		public:

			// default constructor [6/28/2023 Payvand]

			Element2d()
			{}

			// constructors [6/28/2023 Payvand]

			Element2d
			(
				const Standard_Integer theIndex, 
				const std::array<std::shared_ptr<Edge2d>, nbEdges>& theEdges
			)
				: Global_Indexed(theIndex)
				, theEdges_(theEdges)
			{}

			Element2d
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Edge2d>, nbEdges>&& theEdges
			)
				: Global_Indexed(theIndex)
				, theEdges_(std::move(theEdges))
			{}

			// Public functions and operators [6/28/2023 Payvand]

			const auto& Edges() const { return theEdges_; }
			auto& EdgesRef() { return theEdges_; }

			const auto& Back() const { return theBack_; }
			auto& BackRef() { return theBack_; }

			const auto& Front() const { return theFront_; }
			auto& FrontRef() { return theFront_; }

			const auto& Element3d() const { return theElement_; }
			auto& Element3dRef() { return theElement_; }

		};


	private:

		/*Private Data*/

		std::shared_ptr<MeshPost2d_OFTopology> theMesh_;

		Standard_Real theExtrusion_;

		PointList thePoints_;
		CellList theCells_;
		FaceList theFaces_;
		OwnerList theOwners_;
		NeighborList theNeighbors_;

		Standard_Integer theLastFace_;
		
		std::map<word, std::vector<std::pair<word, word>>> theBoundaryConditions_;

		// Private functions and operators [6/27/2023 Payvand]

		//static connectivity::triple ExtrudedFaceIndices(const connectivity::triple&, const Standard_Integer theNbPoints);
		//static connectivity::quadruple ExtrudedFaceIndices(const connectivity::dual& theEdge, const Standard_Integer theNbPoints);

		/*static Standard_Integer 
			ExtrudedNodeIndex
			(
				const Standard_Integer theIndex,
				const Standard_Integer theNbPoints
			);*/

		static TnbMeshPost_EXPORT std::vector<std::shared_ptr<Node>> 
			CalcNodes(const std::vector<Pnt2d>&, const Standard_Real theExtrusion);

		TnbMeshPost_EXPORT std::tuple
			<
			std::vector<std::shared_ptr<Element2d>>,
			std::vector<std::shared_ptr<Edge2d>>, 
			std::vector<std::shared_ptr<Node2d>>
			>
			CalcMesh2d
			(
				const std::vector<std::shared_ptr<Node>>&
			);

		static TnbMeshPost_EXPORT std::vector<std::shared_ptr<Node2d>>
			CalcNodes2d(const std::vector<std::shared_ptr<Node>>&);
		static TnbMeshPost_EXPORT std::vector<std::pair<Standard_Integer, Standard_Integer>>
			RetrieveBoundaries(const std::map<word, std::pair<Standard_Integer, Standard_Integer>>&);
		static TnbMeshPost_EXPORT std::tuple
			<
			std::shared_ptr<Node2d>,
			std::shared_ptr<Node2d>, 
			std::shared_ptr<Node2d>
			>
			RetrieveNodes(const Element2d&);
		static TnbMeshPost_EXPORT void CreateFace(const std::shared_ptr<Edge2d>&);
		static TnbMeshPost_EXPORT void CreateFace(const std::shared_ptr<Element2d>&, const Standard_Integer theIndex);
		static TnbMeshPost_EXPORT void CalcFaces(const std::vector<std::shared_ptr<Edge2d>>&);
		static TnbMeshPost_EXPORT void CalcFaces(const std::vector<std::shared_ptr<Element2d>>&, const Standard_Integer theNbEdges);
		static TnbMeshPost_EXPORT void CalcElements(const std::vector<std::shared_ptr<Element2d>>&);

		// renumbering [7/3/2023 Payvand]

		/*static std::pair<std::vector<std::shared_ptr<Edge2d>>, std::vector<std::shared_ptr<Edge2d>>> 
			SeperateEdges(const std::vector<std::shared_ptr<Edge2d>>&);
		static void RenumberInteriors(const std::vector<std::shared_ptr<Edge2d>>&);
		static void RenumberBoundaries(const std::vector<std::shared_ptr<Edge2d>>&, const Standard_Integer theNbInteriors);;
		static void Renumber(const std::vector<std::shared_ptr<Edge2d>>&);*/

		// retrieving the OpenFOAM files [7/1/2023 Payvand]

		static TnbMeshPost_EXPORT PointList RetrievePointList(const std::vector<std::shared_ptr<Node>>&);

		static TnbMeshPost_EXPORT CellList RetrieveCellList(const std::vector<std::shared_ptr<Element2d>>&);
		static TnbMeshPost_EXPORT FaceList RetrieveFaceList(const std::vector<std::shared_ptr<Edge2d>>&, const std::vector<std::shared_ptr<Element2d>>&);
		static TnbMeshPost_EXPORT OwnerList RetrieveOwnerList(const std::vector<std::shared_ptr<Edge2d>>&, const std::vector<std::shared_ptr<Element2d>>&);
		static TnbMeshPost_EXPORT NeighborList RetrieveNeighborList(const std::vector<std::shared_ptr<Edge2d>>&);

		static TnbMeshPost_EXPORT Cell RetrieveCell(const Element2d&);
		static TnbMeshPost_EXPORT Face RetrieveFace(const Edge2d&);
		static TnbMeshPost_EXPORT std::pair<Face, Face> RetrieveFace(const Element2d&);
		

	public:

		// default constructor [6/27/2023 Payvand]

		MeshPost2d_ConvertToOpenFOAM()
		{}

		// constructors [6/27/2023 Payvand]


		// Public functions and operators [6/27/2023 Payvand]

		auto Extrusion() const { return theExtrusion_; }

		const auto& Mesh() const { return theMesh_; }

		TnbMeshPost_EXPORT void Perform();
		TnbMeshPost_EXPORT void Export() const;

		void SetMesh(const std::shared_ptr<MeshPost2d_OFTopology>& theMesh) { theMesh_ = theMesh; }
		TnbMeshPost_EXPORT void SetBoundaryCondition
		(
			const word& theRegion,
			const std::vector<std::pair<word, word>>&
		);

		static TnbMeshPost_EXPORT void WriteOpenFOAMHeader(Ostream&);
		static TnbMeshPost_EXPORT void WriteOpenFOAMSeperator(Ostream&);
	};
}

#endif // !_MeshPost2d_ConvertToOpenFOAM_Header
