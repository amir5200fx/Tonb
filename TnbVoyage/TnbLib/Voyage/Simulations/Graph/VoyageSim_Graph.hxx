#pragma once
#ifndef _VoyageSim_Graph_Header
#define _VoyageSim_Graph_Header

#include <Pnt2d.hxx>
#include <Global_Indexed.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class VoyageWP_Net;

	class VoyageSim_Graph
	{

	public:

		class Edge;

		class NextPos
		{

			/*Private Data*/

			Pnt2d theCoord_;

		public:

			// default constructor

			NextPos()
			{}

			// constructors

			NextPos(const Pnt2d& theCoord)
				: theCoord_(theCoord)
			{}

			// Public functions and operators

			const auto& Coord() const { return theCoord_; }
			
		};

		class Node
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;

			Standard_Real theTime_;
			mutable  Standard_Real theValue_;

			std::map<Standard_Integer, std::shared_ptr<NextPos>> theNextPoses_;

			std::map<Standard_Integer, std::weak_ptr<Edge>>
				theNexts_;

		public:

			// default constructor

			Node()
				: theCoord_(Pnt2d::null)
				, theTime_(0)
				, theValue_(0)
			{}

			// constructors

			Node(const Standard_Integer theIndex, const Pnt2d& theCoord, const Standard_Real theTime)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
				, theValue_(0)
				, theTime_(theTime)
			{}

			Node(const Standard_Integer theIndex, Pnt2d&& theCoord, const Standard_Real theTime)
				: Global_Indexed(theIndex)
				, theCoord_(std::move(theCoord))
				, theTime_(theTime)
				, theValue_(0)
			{}
			

			// Public functions and operators

			virtual Standard_Boolean IsDeparture() const { return Standard_False; }
			virtual Standard_Boolean IsArrival() const { return Standard_False; }

			const auto& Coord() const { return theCoord_; }
			auto Time() const { return theTime_; }
			auto& Value() const { return theValue_; }

			const auto& Nexts() const { return theNexts_; }
			const auto& NextPoses() const { return theNextPoses_; }

			void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
			void SetCoord(Pnt2d&& theCoord) { theCoord_ = std::move(theCoord); }
			void SetTime(const Standard_Real theTime) { theTime_ = theTime; }

			void SetNext(const Standard_Integer, const std::shared_ptr<Edge>&);
			void SetNextPos(const Standard_Integer, const std::shared_ptr<NextPos>&);
			void RemoveNext(const Standard_Integer);
			
		};

		class DeptNode
			: public Node
		{

			/*Private Data*/

		public:

			// default construtcor

			DeptNode()
			{}

			// construtcors

			DeptNode(const Standard_Integer theIndex, const Pnt2d& theCoord, const Standard_Real theTime)
				: Node(theIndex, theCoord, theTime)
			{}

			DeptNode(const Standard_Integer theIndex, Pnt2d&& theCoord, const Standard_Real theTime)
				: Node(theIndex, std::move(theCoord), theTime)
			{}

			// Public functions and operators

			Standard_Boolean IsDeparture() const override { return Standard_True; }
			
		};

		class ArvalNode
			: public Node
		{

			/*Private Data*/

		public:

			// default construtcor

			ArvalNode()
			{}

			// construtcors

			ArvalNode(const Standard_Integer theIndex, const Pnt2d& theCoord, const Standard_Real theTime)
				: Node(theIndex, theCoord, theTime)
			{}

			ArvalNode(const Standard_Integer theIndex, Pnt2d&& theCoord, const Standard_Real theTime)
				: Node(theIndex, std::move(theCoord), theTime)
			{}

			// Public functions and operators

			Standard_Boolean IsDeparture() const override { return Standard_True; }

		};

		class Edge
			: public Global_Indexed
		{

		public:
			
			enum { nbNodes = 2 };

			typedef std::array<std::shared_ptr<Node>, nbNodes>
				Array2;

		private:

			/*Private Data*/

			Array2 theNodes_;

			Standard_Real theDist_;

		public:

			// default constructor

			Edge()
				: theDist_(0)
			{}

			// construtcors

			Edge(const Standard_Integer theIndex, const Array2& theNodes)
				: Global_Indexed(theIndex)
				, theNodes_(theNodes)
				, theDist_(0)
			{}

			Edge(const Standard_Integer theIndex, Array2&& theNodes)
				: Global_Indexed(theIndex)
				, theNodes_(std::move(theNodes))
				, theDist_(0)
			{}

			// Public functions and operators

			const auto& Nodes() const { return theNodes_; }
			auto& NodesRef() { return theNodes_; }

			const std::shared_ptr<Node>& Node0() const;
			const std::shared_ptr<Node>& Node1() const;

			auto Dist() const { return theDist_; }

			void SetNode0(const std::shared_ptr<Node>&);
			void SetNode0(std::shared_ptr<Node>&&);
			void SetNode1(const std::shared_ptr<Node>&);
			void SetNode1(std::shared_ptr<Node>&&);
			void SetDist(const Standard_Real theValue) { theDist_ = theValue; }
			
		};

	private:

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<Edge>> theEdges_;

		std::shared_ptr<Node> theDeparture_;

	public:

		// default constructor

		VoyageSim_Graph()
		{}

		// constructors

		// Public funtions and operators

		const auto& Edges() const { return theEdges_; }
		const auto& Departure() const { return theDeparture_; }
		
		auto& EdgesRef() { return theEdges_; }
		auto& DepartureRef() { return theDeparture_; }

		void SetDeparture(const std::shared_ptr<Node>& theNode) { theDeparture_ = theNode; }
		
	};
}

#endif
