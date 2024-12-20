#pragma once
#ifndef _VoyageWP_Net_Header
#define _VoyageWP_Net_Header

#include <Voyage_Module.hxx>
#include <Entity_Connectivity.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Pnt2d.hxx>
#include <Global_Indexed.hxx>

#include <map>
#include <vector>
#include <memory>

namespace tnbLib
{

	class VoyageWP_Net
	{

	public:

		class Node
			: public Global_Indexed
			, public std::enable_shared_from_this<Node>
		{

			/*Private Data*/

			Pnt2d theCoord_;
			Standard_Boolean theSense_;

			mutable Standard_Real theMinTime_;
			mutable Standard_Real theMaxTime_;

			std::map<Standard_Integer, std::shared_ptr<Node>> theNexts_;
		

		protected:

			//- default constructor

			Node()
				: theSense_(Standard_False)
				, theMinTime_(0)
				, theMaxTime_(0)
			{}

			//- constructors

			Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
				, theSense_(Standard_False)
				, theMinTime_(0)
				, theMaxTime_(0)
			{}

			Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(std::move(theCoord))
				, theSense_(Standard_False)
				, theMinTime_(0)
				, theMaxTime_(0)
			{}

		public:

			//- Public functions and operators

			[[nodiscard]] const auto& Coord() const { return theCoord_; }

			auto& MinTime() const { return theMinTime_; }
			auto& MaxTime() const { return theMaxTime_; }

			[[nodiscard]] virtual Standard_Boolean IsReference() const { return Standard_False; }
			[[nodiscard]] virtual Standard_Boolean IsWP() const { return Standard_False; }

			TnbVoyage_EXPORT Standard_Integer Size() const;
			auto Sense() const { return theSense_; }

			[[nodiscard]] const auto& Nexts() const { return theNexts_; }
			TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>> RetrieveNexts() const;

			TnbVoyage_EXPORT void InsertNode(const Standard_Integer theIndex, const std::shared_ptr<Node>&);
			TnbVoyage_EXPORT void RemoveNode(const Standard_Integer theIndex);
			TnbVoyage_EXPORT void FlushConnects();
			void SetSense(const Standard_Boolean theSense) { theSense_ = theSense; }
			void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
			void SetCoord(Pnt2d&& theCoord) { theCoord_ = std::move(theCoord); }

		};

		//- Forward Declarations
		class WPNode;

		class RefNode
			: public Node
		{

			/*Private Data*/

			mutable Standard_Real theTime_;
			mutable Standard_Real theDist_;

		protected:

			//- default constructor

			TnbVoyage_EXPORT RefNode();

			//- constructors

			RefNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Node(theIndex, theCoord)
				, theTime_(0)
				, theDist_(0)
			{}

			RefNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Node(theIndex, std::move(theCoord))
				, theTime_(0)
				, theDist_(0)
			{}

		public:
			
			virtual ~RefNode() = default;

			//- Public functions and operators

			auto& Time() const { return theTime_; }
			auto& Dist() const { return theDist_; }

			[[nodiscard]] Standard_Boolean IsReference() const override { return Standard_True; }

			[[nodiscard]] virtual Standard_Boolean IsInterior() const { return Standard_False; }
			[[nodiscard]] virtual Standard_Boolean IsDeparture() const { return Standard_False; }
			[[nodiscard]] virtual Standard_Boolean IsArrival() const { return Standard_False; }

			virtual std::vector<std::shared_ptr<Node>> RetrieveNodes() const = 0;

		};

		class InterNode
			: public RefNode
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<WPNode>> theStarboards_;
			std::map<Standard_Integer, std::shared_ptr<WPNode>> thePorts_;

		public:

			//- default constructor

			InterNode()
				= default;

			//- constructors

			InterNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			InterNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: RefNode(theIndex, std::move(theCoord))
			{}

			//- Public functions and operators

			[[nodiscard]] Standard_Boolean IsInterior() const override { return Standard_True; }
			TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>> RetrieveNodes() const override;
			TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>> RetrievePortSides() const;
			TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>> RetrieveStarSides() const;

			TnbVoyage_EXPORT Standard_Integer StarboardSize() const;
			TnbVoyage_EXPORT Standard_Integer PortSize() const;

			[[nodiscard]] const auto& Starboards() const { return theStarboards_; }
			[[nodiscard]] const auto& Ports() const { return thePorts_; }

			TnbVoyage_EXPORT void InsertToStarboard(const Standard_Integer theIndex, const std::shared_ptr<WPNode>&);
			TnbVoyage_EXPORT void InsertToPort(const Standard_Integer theIndex, const std::shared_ptr<WPNode>&);

			TnbVoyage_EXPORT void RemoveFromStarboard(const Standard_Integer theIndex);
			TnbVoyage_EXPORT void RemoveFromPort(const Standard_Integer theIndex);
			TnbVoyage_EXPORT void ClearStarboards();
			TnbVoyage_EXPORT void ClearPorts();

		};

		class DepNode
			: public RefNode
		{

			/*Private Data*/

		public:

			//- default constructor

			DepNode()
				= default;

			//- constructors

			DepNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			DepNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: RefNode(theIndex, std::move(theCoord))
			{}

			//- Public functions and operators

			[[nodiscard]] Standard_Boolean IsDeparture() const override { return Standard_True; }
			TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>> RetrieveNodes() const override;

		};

		class ArvNode
			: public RefNode
		{

			/*Private Data*/

		public:

			//- default constructor

			ArvNode()
				= default;

			//- constructors

			ArvNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			ArvNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: RefNode(theIndex, std::move(theCoord))
			{}

			//- Public functions and operators

			[[nodiscard]] Standard_Boolean IsArrival() const override { return Standard_True; }
			TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>> RetrieveNodes() const override;

		};

		class WPNode
			: public Node
		{

			/*Private Data*/

			std::weak_ptr<InterNode> theRef_;

		public:

			//- default constructor

			WPNode()
				= default;

			//- constructors

			WPNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Node(theIndex, theCoord)
			{}

			WPNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Node(theIndex, std::move(theCoord))
			{}

			//- Public functions and operators

			const auto& Reference() const { return  theRef_; }

			[[nodiscard]] Standard_Boolean IsWP() const override { return Standard_True; }

			void SetReference(const std::weak_ptr<InterNode>& theNode) { theRef_ = theNode; }

		};

	private:

		/*Private Data*/

		std::vector<std::shared_ptr<RefNode>> theNodes_;

	public:

		//- default constructor

		VoyageWP_Net()
			= default;

		//- constructors


		//- Public functions and operators

		[[nodiscard]] TnbVoyage_EXPORT Standard_Integer NbNodes() const;

		[[nodiscard]] const auto& Nodes() const { return theNodes_; }
		auto& NodesRef() { return theNodes_; }

		TnbVoyage_EXPORT std::shared_ptr<Node> Departure() const;
		TnbVoyage_EXPORT std::shared_ptr<Node> Arrival() const;

		[[nodiscard]] TnbVoyage_EXPORT std::shared_ptr<RefNode> GetNode(const Standard_Integer theIndex) const;

		[[nodiscard]] TnbVoyage_EXPORT Standard_Integer NbStarboards(const Standard_Integer theIndex) const;
		[[nodiscard]] TnbVoyage_EXPORT Standard_Integer NbPorts(const Standard_Integer theIndex) const;

		[[nodiscard]] TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>>
			RetrieveUnsortedWaypoints
			(
				const Standard_Integer theIndex,
				const Standard_Integer fromStar,
				const Standard_Integer toPort
			) const;

		TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>>
			Waypoints(const Standard_Integer theIndex) const;
		TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>>
			SortedWaypoints(const Standard_Integer theIndex) const;
		TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>>
			RetrieveWaypoints
			(
				const Standard_Integer theIndex,
				const Standard_Integer fromStar,
				const Standard_Integer toPort
			) const;
		TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>> RetrieveNodes() const;
		TnbVoyage_EXPORT std::vector<Pnt2d> RetrieveCoords() const;
		TnbVoyage_EXPORT std::vector<connectivity::dual> RetrieveConnectivity() const;

		TnbVoyage_EXPORT void FlushConnects() const;

		TnbVoyage_EXPORT void ExportToPlt(OFstream&) const;

		static TnbVoyage_EXPORT std::shared_ptr<Entity2d_Polygon>
			RetrieveCoords(const std::vector<std::shared_ptr<Node>>&);

	};

}

#endif // !_VoyageWP_Net_Header
