#pragma once
#ifndef _VoyageWP_Offset_Header
#define _VoyageWP_Offset_Header

#include <Global_Indexed.hxx>
#include <Global_Done.hxx>

#include <Pnt2d.hxx>
#include <Dir2d.hxx>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageWP_Ref;

	class VoyageWP_Offset
		: public Global_Done
	{

	public:

		//- Forward Declarations

		class Node
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;

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

			virtual ~Node()
			{}

		public:

			//- Public functions and operators

			virtual Standard_Boolean IsRef() const { return Standard_False; }
			virtual Standard_Boolean IsOffset() const { return Standard_False; }

			const auto& Coord() const { return theCoord_; }

			void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
			void SetCoord(Pnt2d&& theCoord) { theCoord_ = std::move(theCoord); }

		};

		class RefNode
			: public Node
		{

			/*Private Data*/

			Dir2d theTangent_;


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

			virtual Standard_Boolean IsDeparture() const { return Standard_False; }
			virtual Standard_Boolean IsArrival() const { return Standard_False; }
			virtual Standard_Boolean IsInterior() const { return Standard_False; }

			Standard_Boolean IsRef() const override { return Standard_True; }

			const auto& Tangent() const { return theTangent_; }

			void SetTangent(const Dir2d& theDir) { theTangent_ = theDir; }
			void SetTangent(Dir2d&& theDir) { theTangent_ = std::move(theDir); }

			
		};

		class InterNode
			: public RefNode
		{

			/*Private Data*/

			std::shared_ptr<Node> theStarboard_;
			std::shared_ptr<Node> thePort_;

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

			const auto& Starboard() const { return theStarboard_; }
			const auto& Port() const { return thePort_; }

			std::pair<Pnt2d, Pnt2d> StarboardProfile() const;
			std::pair<Pnt2d, Pnt2d> PortProfile() const;

			void SetStarboard(const std::shared_ptr<Node>& theNode) { theStarboard_ = theNode; }
			void SetPort(const std::shared_ptr<Node>& theNode) { thePort_ = theNode; }

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

		class OffsetNode
			: public Node
		{

			/*Private Data*/

			std::weak_ptr<Node> theRef_;

		public:

			//- default constructor

			OffsetNode()
			{}

			//- constructors

			OffsetNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Node(theIndex, theCoord)
			{}

			OffsetNode(const Standard_Integer theIndex, Pnt2d& theCoord)
				: Node(theIndex, std::move(theCoord))
			{}

			//- Public functions and operators

			Standard_Boolean IsOffset() const { return Standard_True; }

			const auto& Ref() const { return theRef_; }

			void SetRef(const std::weak_ptr<Node>& theNode) { theRef_ = theNode; }

		};

	private:

		/*Private Data*/

		std::vector<std::shared_ptr<Node>> theRef_;

	public:

		//- default constructor

		VoyageWP_Offset()
		{}

		//- Constructors


		//- Public functions and operators

		const auto& Ref() const { return theRef_; }

		std::vector<std::shared_ptr<Node>> RetrieveInteriors() const;
		std::shared_ptr<Node> Departure() const;
		std::shared_ptr<Node> Arrival() const;

		void CalcOffsets(const VoyageWP_Ref&);

	};
}

#endif // !_VoyageWP_Offset_Header
