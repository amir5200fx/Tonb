#pragma once
#ifndef _VoyageWP_Ref_Header
#define _VoyageWP_Ref_Header

#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Global_Done.hxx>
#include <Global_Indexed.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [9/5/2023 aamir]
	class VoyageMesh_Element;
	class VoyageMesh_Edge;
	class VoyageMesh_Node;

	class VoyageWP_Ref
		: public Global_Done
	{

	public:

		/*struct RefEnt
		{
			std::pair
				<
				std::shared_ptr<VoyageMesh_Edge>, 
				std::shared_ptr<VoyageMesh_Edge>
				> entity;
		};*/

		typedef std::vector<std::shared_ptr<VoyageMesh_Element>> ElmList;
		typedef std::vector<std::shared_ptr<VoyageMesh_Edge>> EdgeList;

		// Forward Declarations [9/5/2023 aamir]
		class SupEdge;

		class SupNode
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;

		protected:

			// default constructor [9/5/2023 aamir]

			SupNode()
			{}

			// constructors [9/5/2023 aamir]

			SupNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
			{}

			SupNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(std::move(theCoord))
			{}

		public:

			// Public functions and operators [9/5/2023 aamir]

			[[nodiscard]] virtual Standard_Boolean IsInterior() const { return Standard_False; }
			[[nodiscard]] virtual Standard_Boolean IsDeparture() const { return Standard_False; }
			[[nodiscard]] virtual Standard_Boolean IsArrival() const { return Standard_False; }

			[[nodiscard]] virtual Dir2d CalcTangent() const = 0;

			[[nodiscard]] const auto& Coord() const { return theCoord_; }

			void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
			void SetCoord(Pnt2d&& theCoord) { theCoord_ = std::move(theCoord); }
			
		};

		class InterNode
			: public SupNode
		{

			/*Private Data*/

			std::weak_ptr<SupEdge> theBackward_;
			std::weak_ptr<SupEdge> theForward_;

		public:

			// default constructor [9/5/2023 aamir]

			InterNode()
			= default;

			// constructors [9/5/2023 aamir]

			InterNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: SupNode(theIndex, theCoord)
			{}

			InterNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: SupNode(theIndex, std::move(theCoord))
			{}

			// Public functions and operators [9/5/2023 aamir]

			[[nodiscard]] Standard_Boolean IsInterior() const override { return Standard_True; }

			[[nodiscard]] TnbVoyage_EXPORT Dir2d CalcTangent() const override;
			[[nodiscard]] TnbVoyage_EXPORT Pnt2d CalcStarOffset() const;
			[[nodiscard]] TnbVoyage_EXPORT Pnt2d CalcPortOffset() const;

			[[nodiscard]] const auto& Forward() const { return theForward_; }
			[[nodiscard]] const auto& Backward() const { return theBackward_; }

			void SetForward(const std::weak_ptr<SupEdge>& theEdge) { theForward_ = theEdge; }
			void SetBackward(const std::weak_ptr<SupEdge>& theEdge) { theBackward_ = theEdge; }

		};

		class EndNode
			: public SupNode
		{

			/*Private Data*/

		protected:

			// default constructor [9/5/2023 aamir]

			EndNode()
			{}

			// constructors [9/5/2023 aamir]

			EndNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: SupNode(theIndex, theCoord)
			{}

			EndNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: SupNode(theIndex, std::move(theCoord))
			{}

		public:

			// Public functions and operators [9/5/2023 aamir]

		};

		class DepNode
			: public EndNode
		{

			/*Private Data*/

			std::weak_ptr<SupEdge> theForward_;

		public:

			// default constructor [9/5/2023 aamir]

			DepNode()
			= default;

			// constructors [9/5/2023 aamir]

			DepNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: EndNode(theIndex, theCoord)
			{}

			DepNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: EndNode(theIndex, std::move(theCoord))
			{}

			// Public functions and operators [9/5/2023 aamir]

			[[nodiscard]] Standard_Boolean IsDeparture() const override { return Standard_True; }

			TnbVoyage_EXPORT Dir2d CalcTangent() const override;

			[[nodiscard]] const auto& Forward() const { return theForward_; }

			void SetForward(const std::weak_ptr<SupEdge>& theEdge) { theForward_ = theEdge; }

		};

		class ArvNode
			: public EndNode
		{

			/*Private Data*/

			std::weak_ptr<SupEdge> theBackward_;

		public:

			// default constructor [9/5/2023 aamir]

			ArvNode()
			= default;

			// constructors [9/5/2023 aamir]

			ArvNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: EndNode(theIndex, theCoord)
			{}

			ArvNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: EndNode(theIndex, std::move(theCoord))
			{}

			// Public functions and operators [9/5/2023 aamir]

			[[nodiscard]] Standard_Boolean IsArrival() const override { return Standard_True; }

			TnbVoyage_EXPORT Dir2d CalcTangent() const override;

			[[nodiscard]] const auto& Backward() const { return theBackward_; }

			void SetBackward(const std::weak_ptr<SupEdge>& theEdge) { theBackward_ = theEdge; }

		};

		class SupEdge
			: public Global_Indexed
		{

			/*Private Data*/

			std::shared_ptr<SupNode> theNode0_;
			std::shared_ptr<SupNode> theNode1_;

			std::shared_ptr<VoyageMesh_Edge> theStarboard_;
			std::shared_ptr<VoyageMesh_Edge> thePort_;

		public:

			// default constructor [9/5/2023 aamir]

			SupEdge()
			= default;

			// constructors [9/5/2023 aamir]

			SupEdge
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<SupNode>& theNode0, 
				const std::shared_ptr<SupNode>& theNode1
			)
				: Global_Indexed(theIndex)
				, theNode0_(theNode0)
				, theNode1_(theNode1)
			{}

			// Public functions and operators [9/5/2023 aamir]

			[[nodiscard]] const auto& Node0() const { return theNode0_; }
			[[nodiscard]] const auto& Node1() const { return theNode1_; }

			[[nodiscard]] const auto& Starboard() const { return theStarboard_; }
			[[nodiscard]] const auto& Port() const { return thePort_; }

			TnbVoyage_EXPORT std::shared_ptr<VoyageMesh_Node> RetrieveStarTip() const;
			TnbVoyage_EXPORT std::shared_ptr<VoyageMesh_Node> RetrievePortTip() const;
			TnbVoyage_EXPORT std::shared_ptr<VoyageMesh_Element> RetrieveStarElement() const;
			TnbVoyage_EXPORT std::shared_ptr<VoyageMesh_Element> RetrievePortElement() const;

			TnbVoyage_EXPORT Dir2d CalcTangent() const;

			void SetNode0(const std::shared_ptr<SupNode>& theNode) { theNode0_ = theNode; }
			void SetNode1(const std::shared_ptr<SupNode>& theNode) { theNode1_ = theNode; }

			void SetStarboard(const std::shared_ptr<VoyageMesh_Edge>& theEdge) { theStarboard_ = theEdge; }
			void SetPort(const std::shared_ptr<VoyageMesh_Edge>& theEdge) { thePort_ = theEdge; }
		};

	private:

		/*Private Data*/

		std::vector<std::shared_ptr<SupEdge>> theEntities_;

	public:

		static TnbVoyage_EXPORT Standard_Real DEFAULT_TOL;

		// default constructor [9/5/2023 aamir]

		VoyageWP_Ref()
		= default;

		// constructors [9/5/2023 aamir]

		// Public functions and operators [9/5/2023 aamir]

		[[nodiscard]] const auto& Entities() const { return theEntities_; }

		TnbVoyage_EXPORT std::shared_ptr<SupNode> Departure() const;
		TnbVoyage_EXPORT std::shared_ptr<SupNode> Arrival() const;

		// Static functions and operators [9/5/2023 aamir]

		TnbVoyage_EXPORT void CalcReference(const EdgeList& theStarboard, const EdgeList& thePort);


		// Static functions and operators [9/6/2023 aamir]

		static TnbVoyage_EXPORT std::shared_ptr<VoyageMesh_Element> RetrieveStarElement(const SupEdge&);
		static TnbVoyage_EXPORT std::shared_ptr<VoyageMesh_Element> RetrievePortElement(const SupEdge&);

		static TnbVoyage_EXPORT Pnt2d FirstCoord(const SupEdge&);
		static TnbVoyage_EXPORT Pnt2d SecondCoord(const SupEdge&);

	};

}

#endif // !_VoyageWP_Ref_Header
