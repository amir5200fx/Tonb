#pragma once
#ifndef _Cad2d_IdentRings_Segment_Header
#define _Cad2d_IdentRings_Segment_Header

#include <Cad2d_IdentRings_Link.hxx>

namespace tnbLib
{

	namespace cad2dLib
	{

		class IdentRings_Segment
			: public IdentRings_Link
		{

			/*Private Data*/

			std::shared_ptr<IdentRings_Node> theNode0_;
			std::shared_ptr<IdentRings_Node> theNode1_;

		public:

			// default constructor [1/24/2022 Amir]

			IdentRings_Segment()
			{}


			// constructors [1/24/2022 Amir]

			IdentRings_Segment
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<IdentRings_Node>& theNode0,
				const std::shared_ptr<IdentRings_Node>& theNode1,
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			)
				: IdentRings_Link(theIndex, theEdges)
				, theNode0_(theNode0)
				, theNode1_(theNode1)
			{}

			IdentRings_Segment
			(
				const Standard_Integer theIndex,
				std::shared_ptr<IdentRings_Node>&& theNode0,
				std::shared_ptr<IdentRings_Node>&& theNode1,
				std::vector<std::shared_ptr<Pln_Edge>>&& theEdges
			)
				: IdentRings_Link(theIndex, std::move(theEdges))
				, theNode0_(std::move(theNode0))
				, theNode1_(std::move(theNode1))
			{}


			// override functions and operators [1/24/2022 Amir]

			Standard_Boolean IsSegment() const override
			{
				return Standard_True;
			}

			TnbCad2d_EXPORT void Attach() override;
			TnbCad2d_EXPORT void Detach() override;

			// public functions and operators [1/26/2022 Amir]

			const auto& Node0() const
			{
				return theNode0_;
			}

			const auto& Node1() const
			{
				return theNode1_;
			}

			void SetNode0(const std::shared_ptr<IdentRings_Node>& theNode)
			{
				theNode0_ = theNode;
			}

			void SetNode0(std::shared_ptr<IdentRings_Node>&& theNode)
			{
				theNode0_ = std::move(theNode);
			}

			void SetNode1(const std::shared_ptr<IdentRings_Node>& theNode)
			{
				theNode1_ = theNode;
			}

			void SetNode1(std::shared_ptr<IdentRings_Node>&& theNode)
			{
				theNode1_ = std::move(theNode);
			}
		};
	}
}

#endif // !_Cad2d_IdentRings_Segment_Header
