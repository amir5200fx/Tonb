#pragma once
#ifndef _MeshPost_Extrude_Header
#define _MeshPost_Extrude_Header

#include <MeshPost_Module.hxx>
#include <Geo3d_FVMeshFwd.hxx>
#include <Pnt3d.hxx>
#include <Pnt2d.hxx>
#include <Global_Indexed.hxx>
#include <Global_Done.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	//- Forward Declarations
	class MeshIO3d_PentaFEA;
	class MeshPost2d_OFTopology;

	class MeshPost_Extrude
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

		class Cell
		{

		public:

			enum
			{
				nbNodes = 6
			};

		private:

			// Private Data [6/27/2023 Payvand]

			std::array<Standard_Integer, nbNodes> theNodes_;

		public:

			// default constructor [6/27/2023 Payvand]

			Cell()
			{}

			// constructors [6/27/2023 Payvand]

			Cell(const std::array<Standard_Integer, nbNodes>& theNodes)
				: theNodes_(theNodes)
			{}

			Cell(std::array<Standard_Integer, nbNodes>&& theNodes)
				: theNodes_(std::move(theNodes))
			{}


			// Public functions and operators [6/27/2023 Payvand]

			const auto& Nodes() const { return theNodes_; }
			auto& NodesRef() { return theNodes_; }

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

			virtual ~Node() {}

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

		//class QuadFacet
		//	: public Facet
		//{

		//public:

		//	enum
		//	{
		//		nbNodes = 4
		//	};

		//private:

		//	/*Private Data*/

		//	std::array<std::shared_ptr<Node>, nbNodes> theNodes_;

		//public:

		//	// default constructor [6/27/2023 Payvand]

		//	QuadFacet()
		//	{}

		//	// constructors [6/27/2023 Payvand]

		//	QuadFacet
		//	(
		//		const Standard_Integer theIndex,
		//		const std::array<std::shared_ptr<Node>, nbNodes>& theNodes
		//	)
		//		: Facet(theIndex)
		//		, theNodes_(theNodes)
		//	{}

		//	QuadFacet
		//	(
		//		const Standard_Integer theIndex,
		//		std::array<std::shared_ptr<Node>, nbNodes>&& theNodes
		//	)
		//		: Facet(theIndex)
		//		, theNodes_(std::move(theNodes))
		//	{}


		//	// Public functions and operators [6/27/2023 Payvand]

		//	const auto& Nodes() const { return theNodes_; }
		//	auto& NodesRef() { return theNodes_; }

		//	Standard_Integer NbNodes() const override { return (Standard_Integer)nbNodes; }
		//	TnbMeshPost_EXPORT std::vector<std::shared_ptr<Node>> GetNodes() const override;
		//};
		
		class Element
			: public Global_Indexed
		{

		public:

			enum
			{
				nbNodes = 6
			};

		private:

			/*Private Data*/

			std::array<std::shared_ptr<Node>, nbNodes> theNodes_;


		public:

			// default constructor [6/27/2023 Payvand]

			Element()
			{}

			// constructors [6/27/2023 Payvand]

			Element
			(
				const Standard_Integer theIndex,
				const std::array<std::shared_ptr<Node>, nbNodes>& theNodes
			)
				: Global_Indexed(theIndex)
				, theNodes_(theNodes)
			{}

			Element
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Node>, nbNodes>&& theNodes
			)
				: Global_Indexed(theIndex)
				, theNodes_(std::move(theNodes))
			{}

			// Public functions and operators [6/27/2023 Payvand]

			const auto& Nodes() const { return theNodes_; }
			auto& Nodes() { return theNodes_; }

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

			//void SetSense(const Standard_Boolean theSense) { theSense_ = theSense; }
		};

		class Element2d
			: public Global_Indexed
		{

		public:

			enum
			{
				nbNodes = 3
			};

		private:

			/*Private Data*/

			std::array<std::shared_ptr<Node2d>, nbNodes> theNodes_;

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
				const std::array<std::shared_ptr<Node2d>, nbNodes>& theNodes
			)
				: Global_Indexed(theIndex)
				, theNodes_(theNodes)
			{}

			Element2d
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Node2d>, nbNodes>&& theNodes
			)
				: Global_Indexed(theIndex)
				, theNodes_(std::move(theNodes))
			{}

			// Public functions and operators [6/28/2023 Payvand]

			const auto& Nodes() const { return theNodes_; }
			auto& NodesRef() { return theNodes_; }

			const auto& Back() const { return theBack_; }
			auto& BackRef() { return theBack_; }

			const auto& Front() const { return theFront_; }
			auto& FrontRef() { return theFront_; }

			const auto& Element3d() const { return theElement_; }
			auto& Element3dRef() { return theElement_; }

		};

	private:

		/*Private Data*/

		word theTitle_;

		std::shared_ptr<MeshPost2d_OFTopology> theMesh2d_;

		Standard_Real theExtrusion_;

		PointList thePoints_;
		CellList theCells_;

		Standard_Integer theLastFace_;

		std::map<word, std::vector<Face>> theBoundaryConditions_;


		//- Private functions and operators

		static TnbMeshPost_EXPORT std::vector<std::shared_ptr<Node2d>>
			CalcNodes2d(const std::vector<std::shared_ptr<Node>>&);

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
		
		static TnbMeshPost_EXPORT std::tuple
			<
			std::shared_ptr<Node2d>,
			std::shared_ptr<Node2d>,
			std::shared_ptr<Node2d>
			>
			RetrieveNodes(const Element2d&);
		static TnbMeshPost_EXPORT void CreateFace(const std::shared_ptr<Element2d>&, const Standard_Integer theIndex);
		static TnbMeshPost_EXPORT void CalcFaces(const std::vector<std::shared_ptr<Element2d>>&, const Standard_Integer theNbEdges);
		static TnbMeshPost_EXPORT void CalcElements(const std::vector<std::shared_ptr<Element2d>>&);

		static TnbMeshPost_EXPORT PointList RetrievePointList(const std::vector<std::shared_ptr<Node>>&);
		static TnbMeshPost_EXPORT CellList RetrieveCellList(const std::vector<std::shared_ptr<Element2d>>&);

		static TnbMeshPost_EXPORT Cell RetrieveCell(const Element2d&);

	public:

		//- default constructor

		MeshPost_Extrude()
			: theTitle_("extruded")
		{}

		//- constructors

		//- Public functions and operators

		const auto& Title() const { return theTitle_; }
		const auto& Mesh2d() const { return theMesh2d_; }

		auto Extrusion() const { return theExtrusion_; }

		TnbMeshPost_EXPORT std::shared_ptr<Geo3d_FVMesh> RetrieveIO() const;

		TnbMeshPost_EXPORT void Perform();

		void SetMesh2d(const std::shared_ptr<MeshPost2d_OFTopology>& theMesh) { theMesh2d_ = theMesh; }
		void SetMesh2d(std::shared_ptr<MeshPost2d_OFTopology>&& theMesh) { theMesh2d_ = std::move(theMesh); }

		void SetTitle(const std::string& theName) { theTitle_ = theName; }

	};
}

#endif // !_MeshPost_Extrude_Header
