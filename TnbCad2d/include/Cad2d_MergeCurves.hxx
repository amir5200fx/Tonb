#pragma once
#ifndef _Cad2d_MergeCurves_Header
#define _Cad2d_MergeCurves_Header

#include <Global_Done.hxx>
#include <Global_Indexed.hxx>
#include <Pnt2d.hxx>
#include <Cad2d_Module.hxx>

#include <memory>
#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations [3/21/2022 Amir]
	class Pln_Edge;
	class Pln_Vertex;
	class Cad2d_MergeCurvesInfo;

	class Cad2d_MergeCurves
		: public Global_Done
	{

	public:

		class Node
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;
			Standard_Real theTol_;

			std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>>
				theVertices_;

		public:

			typedef Pnt2d ptType;

			// default constructor [3/21/2022 Amir]


			// constructors [3/21/2022 Amir]

			Node(const Standard_Integer theIndex)
				: Global_Indexed(theIndex)
			{}

			// public functions and operators [3/21/2022 Amir]

			const auto& Coord() const
			{
				return theCoord_;
			}

			auto Tolerance() const
			{
				return theTol_;
			}

			const auto& Vertices() const
			{
				return theVertices_;
			}

			auto NbVertices() const
			{
				return (Standard_Integer)theVertices_.size();
			}

			TnbCad2d_EXPORT void InsertTo(const Standard_Integer theIndex, const std::shared_ptr<Pln_Vertex>& theVtx);
			
			void SetTolerance(const Standard_Real theTol)
			{
				theTol_ = theTol;
			}

			void SetCoord(const Pnt2d& theCoord)
			{
				theCoord_ = theCoord;
			}

			void SetCoord(Pnt2d&& theCoord)
			{
				theCoord_ = std::move(theCoord);
			}

			static TnbCad2d_EXPORT const Pnt2d& GetCoord(const std::shared_ptr<Node>& theNode);
		};

		class Link
			: public Global_Indexed
		{

			/*Private Data*/

			std::shared_ptr<Pln_Edge> theCurve_;

		public:

			// default constructor [3/21/2022 Amir]

			Link()
			{}

			// constructors [3/21/2022 Amir]

			explicit Link(const Standard_Integer theIndex)
				: Global_Indexed(theIndex)
			{}

			// public functions and operators [3/21/2022 Amir]

			virtual Standard_Boolean IsRing() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsSegment() const
			{
				return Standard_False;
			}

			const auto& Curve() const
			{
				return theCurve_;
			}

			void SetCurve(const std::shared_ptr<Pln_Edge>& theCurve)
			{
				theCurve_ = theCurve;
			}
		};

		class RingLink
			: public Link
		{

			/*Private Data*/

			std::shared_ptr<Node> theNode_;

		public:

			// default constructor [3/21/2022 Amir]

			RingLink()
			{}


			// constructors [3/21/2022 Amir]


			RingLink
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Node>& theNode
			)
				: Link(theIndex)
				, theNode_(theNode)
			{}

			RingLink
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Node>&& theNode
			)
				: Link(theIndex)
				, theNode_(std::move(theNode))
			{}

			// override functions and operators [3/21/2022 Amir]

			Standard_Boolean IsRing() const override
			{
				return Standard_True;
			}

			// public functions and operators [3/21/2022 Amir]

			const auto& GetNode() const
			{
				return theNode_;
			}

			void SetNode(const std::shared_ptr<Node>& theNode)
			{
				theNode_ = theNode;
			}
		};

		class SegmentLink
			: public Link
		{

			/*Private Data*/

			std::shared_ptr<Node> theNode0_;
			std::shared_ptr<Node> theNode1_;

		public:

			// default constructor [3/21/2022 Amir]

			SegmentLink()
			{}

			// constructors [3/21/2022 Amir]

			SegmentLink
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Node>& theNode0, 
				const std::shared_ptr<Node>& theNode1
			)
				: Link(theIndex)
				, theNode0_(theNode0)
				, theNode1_(theNode1)
			{}

			SegmentLink
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Node>&& theNode0,
				std::shared_ptr<Node>&& theNode1
			)
				: Link(theIndex)
				, theNode0_(std::move(theNode0))
				, theNode1_(std::move(theNode1))
			{}

			// override functions and operators [3/21/2022 Amir]

			Standard_Boolean IsSegment() const override
			{
				return Standard_True;
			}

			// public functions and operators [3/21/2022 Amir]

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
		};

		// static functions and operators [3/21/2022 Amir]
		
		static TnbCad2d_EXPORT std::map<Standard_Integer, std::shared_ptr<Node>> RetrieveNodes(const std::vector<std::shared_ptr<Link>>&);
		static TnbCad2d_EXPORT std::shared_ptr<Pln_Vertex> MergeNode(const std::shared_ptr<Node>&);

	private:

		/*Private Data*/

		std::shared_ptr<Cad2d_MergeCurvesInfo> theInfo_;

		const std::vector<std::shared_ptr<Pln_Edge>>& theCurves_;


		// private functions [3/21/2022 Amir]

		TnbCad2d_EXPORT std::vector<std::shared_ptr<Link>> CreateLinks(const std::vector<std::shared_ptr<Pln_Edge>>&) const;
		static TnbCad2d_EXPORT std::vector<Pnt2d> RetrieveCoords(const std::vector<std::shared_ptr<Pln_Edge>>&);

	public:

		static TnbCad2d_EXPORT const std::shared_ptr<Cad2d_MergeCurvesInfo> DEFAULT_INFO;

		// default constructor [3/21/2022 Amir]


		// constructors [3/21/2022 Amir]

		explicit Cad2d_MergeCurves
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theCurves
		)
			: theCurves_(theCurves)
			, theInfo_(DEFAULT_INFO)
		{}

		Cad2d_MergeCurves
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theCurves,
			const std::shared_ptr<Cad2d_MergeCurvesInfo>& theInfo
		)
			: theCurves_(theCurves)
			, theInfo_(theInfo)
		{}

		// public functions and operators [3/21/2022 Amir]

		const auto& Curves() const
		{
			return theCurves_;
		}

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		TnbCad2d_EXPORT void Perform();


		// static functions and operators [3/22/2022 Amir]

		static TnbCad2d_EXPORT void Renumber(const std::vector<std::shared_ptr<Pln_Edge>>&);
	};
}

#endif // !_Cad2d_MergeCurves_Header
