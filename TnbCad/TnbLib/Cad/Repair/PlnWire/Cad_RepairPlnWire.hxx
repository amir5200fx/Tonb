#pragma once
#ifndef _Cad_RepairPlnWire_Header
#define _Cad_RepairPlnWire_Header

#include <Pnt2d.hxx>
#include <Vec2d.hxx>
#include <Global_Indexed.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>
#include <exception>
#include <vector>

namespace tnbLib
{

	class Cad_RepairPlnWire_Base
	{

	public:

		class zeroIntPoint
			: public std::exception
		{

			virtual const char* what() const throw()
			{
				return "no intersection has been found.";
			}
		};

		static const zeroIntPoint zeroIntPointObj;
	};

	template<class WireType>
	class Cad_RepairPlnWire
		: public Cad_RepairPlnWire_Base
	{

		typedef typename WireType::paraCurveType paraCurveType;

		/*Private Data*/

		// Forward Declarations [6/21/2022 Amir]
		class Link;
		class Segment;
		class Ring;

		class SegmentNodeAdaptor
		{

			/*Private Data*/

			std::weak_ptr<Segment> theBackward_;
			std::weak_ptr<Segment> theForward_;

		protected:

			// default constructor [2/20/2022 Amir]

			SegmentNodeAdaptor()
			{}

			// constructors [2/20/2022 Amir]

		public:

			// public functions and operators [2/20/2022 Amir]

			const auto& BackwardLink() const
			{
				return theBackward_;
			}

			const auto& ForwardLink() const
			{
				return theForward_;
			}

			Standard_Integer NbSegments() const
			{
				Standard_Integer nbSegments = 0;
				if (ForwardLink().lock())
					nbSegments++;
				if (BackwardLink().lock())
					nbSegments++;
				return nbSegments;
			}

			Standard_Boolean IsManifold() const
			{
				return NbSegments() IS_EQUAL 2;
			}

			void SetBackward(const std::shared_ptr<Segment>& theLink)
			{
				theBackward_ = theLink;
			}

			void SetForward(const std::shared_ptr<Segment>& theLink)
			{
				theForward_ = theLink;
			}
		};

		class RingNodeAdaptor
		{

			/*Private Data*/

			std::weak_ptr<Ring> theRing_;

		protected:

			// default constructor [2/20/2022 Amir]

			RingNodeAdaptor()
			{}

			// constructors [2/20/2022 Amir]

		public:

			const auto& GetRing() const
			{
				return theRing_;
			}

			void SetRing(const std::weak_ptr<Ring>& theRing)
			{
				theRing_ = theRing;
			}

		};

		class Node
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;

		protected:

			// default constructor [2/20/2022 Amir]

			Node()
				: theCoord_(Pnt2d::null)
			{}

			// constructors [2/20/2022 Amir]

			Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
			{}

			Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(std::move(theCoord))
			{}

		public:

			// public functions and operators [2/20/2022 Amir]

			const auto& Coord() const
			{
				return theCoord_;
			}

			void SetCoord(const Pnt2d& theCoord)
			{
				theCoord_ = theCoord;
			}

			void SetCoord(Pnt2d&& theCoord)
			{
				theCoord_ = std::move(theCoord);
			}


			virtual Standard_Boolean IsRing() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsSegment() const
			{
				return Standard_False;
			}
		};

		class RingNode
			: public Node
			, public RingNodeAdaptor
		{

			/*Private Data*/

		public:

			// default constructor [2/20/2022 Amir]

			RingNode()
			{}

			// constructors [2/20/2022 Amir]

			RingNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Node(theIndex, theCoord)
			{}

			RingNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Node(theIndex, std::move(theCoord))
			{}


			// override functions and operators [2/20/2022 Amir]

			Standard_Boolean IsRing() const override
			{
				return Standard_True;
			}

			// public functions and operators [2/20/2022 Amir]
		};

		class SegmentNode
			: public Node
			, public SegmentNodeAdaptor
		{

			/*Private Data*/

		public:

			// default constructor [2/20/2022 Amir]

			SegmentNode()
			{}

			// constructors [2/20/2022 Amir]

			SegmentNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Node(theIndex, theCoord)
			{}

			SegmentNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Node(theIndex, std::move(theCoord))
			{}

			// override functions and operators [2/20/2022 Amir]

			Standard_Boolean IsSegment() const override
			{
				return Standard_True;
			}

			// public functions and operators [2/20/2022 Amir]

		};

		class Link
			: public Global_Indexed
		{

			/*Private Data*/

			std::shared_ptr<paraCurveType> theCurve_;

		protected:

			// default constructor [2/20/2022 Amir]

			Link()
			{}

			// constructors [2/20/2022 Amir]

			Link
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<paraCurveType>& theCurve
			)
				: Global_Indexed(theIndex)
				, theCurve_(theCurve)
			{}

			Link
			(
				const Standard_Integer theIndex,
				std::shared_ptr<paraCurveType>&& theCurve
			)
				: Global_Indexed(theIndex)
				, theCurve_(std::move(theCurve))
			{}

		public:

			// public functions and operators [2/20/2022 Amir]

			const auto& GetCurve() const
			{
				return theCurve_;
			}

			virtual Standard_Boolean IsRing() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsSegment() const
			{
				return Standard_False;
			}

		};

		class Segment
			: public Link
		{

			/*Private Data*/

			std::shared_ptr<Node> theNode0_;
			std::shared_ptr<Node> theNode1_;

		public:

			// default constructor [2/20/2022 Amir]

			Segment()
			{}

			// constructors [2/20/2022 Amir]

			Segment
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<paraCurveType>& theCurve,
				const std::shared_ptr<Node>& theNode0,
				const std::shared_ptr<Node>& theNode1
			)
				: Link(theIndex, theCurve)
				, theNode0_(theNode0)
				, theNode1_(theNode1)
			{}

			Segment
			(
				const Standard_Integer theIndex,
				std::shared_ptr<paraCurveType>&& theCurve,
				std::shared_ptr<Node>&& theNode0,
				std::shared_ptr<Node>&& theNode1
			)
				: Link(theIndex, std::move(theCurve))
				, theNode0_(std::move(theNode0))
				, theNode1_(std::move(theNode1))
			{}

			// override functions and operators [2/20/2022 Amir]

			Standard_Boolean IsSegment() const override
			{
				return Standard_True;
			}

			// public functions and operators [2/20/2022 Amir]



			const auto& Node0() const
			{
				return theNode0_;
			}

			const auto& Node1() const
			{
				return theNode1_;
			}

			void SetNode0(const std::shared_ptr<Node>& theNode)
			{
				theNode0_ = theNode;
			}

			void SetNode1(const std::shared_ptr<Node>& theNode)
			{
				theNode1_ = theNode;
			}

			void SetNode0(std::shared_ptr<Node>&& theNode)
			{
				theNode0_ = std::move(theNode);
			}

			void SetNode1(std::shared_ptr<Node>&& theNode)
			{
				theNode1_ = std::move(theNode);
			}

		};

		class Ring
			: public Link
		{

			/*Private Data*/

			std::shared_ptr<Node> theNode_;

		public:

			// default constructor [2/20/2022 Amir]

			Ring()
			{}

			// constructors [2/20/2022 Amir]

			Ring
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<paraCurveType>& theCurve,
				const std::shared_ptr<Node>& theNode
			)
				: Link(theIndex, theCurve)
				, theNode_(theNode)
			{}

			Ring
			(
				const Standard_Integer theIndex,
				std::shared_ptr<paraCurveType>&& theCurve,
				std::shared_ptr<Node>&& theNode
			)
				: Link(theIndex, std::move(theCurve))
				, theNode_(std::move(theNode))
			{}

			// override functions and operators [2/20/2022 Amir]

			Standard_Boolean IsRing() const override
			{
				return Standard_True;
			}

			// public functions and operators [2/20/2022 Amir]

			const auto& GetNode() const
			{
				return theNode_;
			}

			void SetNode(const std::shared_ptr<Node>& theNode)
			{
				theNode_ = theNode;
			}

			void SetNode(std::shared_ptr<Node>&& theNode)
			{
				theNode_ = std::move(theNode);
			}


		};

		enum class CurvePoint
		{
			start,
			end
		};

	public:

		static Standard_Real 
			GetParameter
			(
				const std::shared_ptr<paraCurveType>& theCurve, 
				const CurvePoint thePoint
			);

		static std::pair<Pnt2d, Vec2d> 
			CalcTangent
			(
				const std::shared_ptr<paraCurveType>& theCurve,
				const CurvePoint thePoint
			);

		static Pnt2d 
			CalcIntersectionPoint
			(
				const Pnt2d& thePoint0,
				const Vec2d& theTang0, 
				const Pnt2d& thePoint1,
				const Vec2d& theTang1
			);

		static void CheckTolerance(const Pnt2d& theCentre, const Pnt2d& thePt, const Standard_Real theTol);

		static std::pair<Pnt2d, Standard_Real> 
			ProjectPoint
			(
				const Pnt2d& theCoord, 
				const std::shared_ptr<paraCurveType>& theCurve
			);

		static std::pair<std::shared_ptr<paraCurveType>, Standard_Boolean> 
			SplitFirstPart
			(
				const Pnt2d& theCoord, 
				const std::shared_ptr<paraCurveType>& theCurve
			);

		static std::pair<std::shared_ptr<paraCurveType>, Standard_Boolean> 
			SplitLastPart
			(
				const Pnt2d& theCoord, 
				const std::shared_ptr<paraCurveType>& theCurve
			);

		static std::pair<std::shared_ptr<paraCurveType>, Standard_Boolean> 
			SplitCurve
			(
				const Pnt2d& theCoord, 
				const std::shared_ptr<paraCurveType>& theCurve,
				const CurvePoint thePt
			);

		static Pnt2d 
			CalcCornerPoint
			(
				const std::shared_ptr<paraCurveType>& theCurve0, 
				const std::shared_ptr<paraCurveType>& theCurve1
			);

		static std::pair<std::shared_ptr<paraCurveType>, std::shared_ptr<paraCurveType>> 
			TrimCornerCurves
			(
				const std::shared_ptr<paraCurveType>& theCurve0, 
				const std::shared_ptr<paraCurveType>& theCurve1
			);

		static Standard_Integer MaxIndex(const std::vector<std::shared_ptr<paraCurveType>>& theCurves);

		static void CheckDuplicateIndex(const std::vector<std::shared_ptr<paraCurveType>>& theCurves);

		static std::vector<std::shared_ptr<paraCurveType>> 
			TrimCurves
			(
				const std::vector<std::shared_ptr<paraCurveType>>& theCurves
			);

		static std::shared_ptr<SegmentNode> 
			CreateNode
			(
				const std::shared_ptr<paraCurveType>& theCurve0, 
				const std::shared_ptr<paraCurveType>& theCurve1, 
				const Standard_Real theTol
			);

		static std::vector<std::shared_ptr<Link>>
			CreateWire
			(
				const std::shared_ptr<paraCurveType>& theCurve,
				const Standard_Real theTol
			);

		static std::vector<std::shared_ptr<Link>> 
			CreateWire
			(
				const std::vector<std::shared_ptr<paraCurveType>>& theCurves, 
				const Standard_Real theTol
			);

		static std::vector<std::shared_ptr<Link>>
			CreateWire
			(
				const std::shared_ptr<WireType>& theCurves,
				const Standard_Real theTol
			);

		static void CheckWire(const std::vector<std::shared_ptr<Link>>&);
		static void CheckWire(const std::shared_ptr<WireType>& theWire, const Standard_Real theTol);

		static std::shared_ptr<WireType> CreateWire(const std::vector<std::shared_ptr<Link>>&);

		

	};
}

#include <Cad_RepairPlnWireI.hxx>

#endif // !_Cad_RepairPlnWire_Header
