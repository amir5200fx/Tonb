#pragma once
#ifndef _VoyageWP_Net_Header
#define _VoyageWP_Net_Header

#include <Voyage_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Pnt2d.hxx>
#include <Global_Indexed.hxx>

#include <map>
#include <vector>
#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class VoyageWP_Net
	{

	public:

		class Node
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;

			std::map<Standard_Integer, std::shared_ptr<Node>> theNexts_;

		protected:

			//- default constructor

			Node()
			{}

			//- constructors

			Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
			{}

			Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(std::move(theCoord))
			{}

		public:

			//- Public functions and operators

			const auto& Coord() const { return theCoord_; }

			virtual Standard_Boolean IsReference() const { return Standard_False; }
			virtual Standard_Boolean IsWP() const { return Standard_False; }

			TnbVoyage_EXPORT Standard_Integer Size() const;

			const auto& Nexts() const { return theNexts_; }

			TnbVoyage_EXPORT void InsertNode(const Standard_Integer theIndex, const std::shared_ptr<Node>&);
			TnbVoyage_EXPORT void RemoveNode(const Standard_Integer theIndex);
			void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
			void SetCoord(Pnt2d&& theCoord) { theCoord_ = std::move(theCoord); }

		};

		//- Forward Declarations
		class WPNode;

		class RefNode
			: public Node
		{

			/*Private Data*/		

		protected:

			//- default constructor

			RefNode()
			{}

			//- constructors

			RefNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Node(theIndex, theCoord)
			{}

			RefNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Node(theIndex, std::move(theCoord))
			{}

		public:

			//- Public functions and operators

			Standard_Boolean IsReference() const override { return Standard_True; }

			virtual Standard_Boolean IsInterior() const { return Standard_False; }
			virtual Standard_Boolean IsDeparture() const { return Standard_False; }
			virtual Standard_Boolean IsArrival() const { return Standard_False; }

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
			{}

			//- constructors

			InterNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			InterNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: RefNode(theIndex, std::move(theCoord))
			{}

			//- Public functions and operators

			Standard_Boolean IsInterior() const { return Standard_True; }

			TnbVoyage_EXPORT Standard_Integer StarboardSize() const;
			TnbVoyage_EXPORT Standard_Integer PortSize() const;

			const auto& Starboards() const { return theStarboards_; }
			const auto& Ports() const { return thePorts_; }

			TnbVoyage_EXPORT void InsertToStarboard(const Standard_Integer theIndex, const std::shared_ptr<WPNode>&);
			TnbVoyage_EXPORT void InsertToPort(const Standard_Integer theIndex, const std::shared_ptr<WPNode>&);

			TnbVoyage_EXPORT void RemoveFromStarboard(const Standard_Integer theIndex);
			TnbVoyage_EXPORT void RemoveFromPort(const Standard_Integer theIndex);

		};

		class DepNode
			: public RefNode
		{

			/*Private Data*/

		public:

			//- default constructor

			DepNode()
			{}

			//- constructors

			DepNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			DepNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: RefNode(theIndex, std::move(theCoord))
			{}

			//- Public functions and operators

			Standard_Boolean IsDeparture() const override { return Standard_True; }

		};

		class ArvNode
			: public RefNode
		{

			/*Private Data*/

		public:

			//- default constructor

			ArvNode()
			{}

			//- constructors

			ArvNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			ArvNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: RefNode(theIndex, std::move(theCoord))
			{}

			//- Public functions and operators

			Standard_Boolean IsArrival() const override { return Standard_True; }

		};

		class WPNode
			: public Node
		{

			/*Private Data*/		

		public:

			//- default constructor

			WPNode()
			{}

			//- constructors

			WPNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Node(theIndex, theCoord)
			{}

			WPNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Node(theIndex, std::move(theCoord))
			{}

			//- Public functions and operators

			Standard_Boolean IsWP() const override { return Standard_True; }

		};

	private:

		/*Private Data*/

		std::vector<std::shared_ptr<RefNode>> theNodes_;

	public:

		//- default constructor

		VoyageWP_Net()
		{}

		//- constructors


		//- Public functions and operators

		Standard_Integer NbNodes() const;

		const auto& Nodes() const { return theNodes_; }
		auto& NodesRef() { return theNodes_; }

		std::vector<std::shared_ptr<Node>> Waypoints(const Standard_Integer theIndex) const;
		std::vector<std::shared_ptr<Node>> RetrieveWaypoints(const Standard_Integer theIndex, const Standard_Integer fromStar, const Standard_Integer toPort);

		static std::shared_ptr<Entity2d_Polygon> RetrieveCoords(const std::vector<std::shared_ptr<Node>>&);

	};

}

#endif // !_VoyageWP_Net_Header
