#pragma once
#ifndef _Cad_MergeParaCurves_Segment_Header
#define _Cad_MergeParaCurves_Segment_Header

#include <Cad_MergeParaCurves_Link.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			class Segment
				: public Link
			{

				/*Private Data*/

				std::shared_ptr<Node> theNode0_;
				std::shared_ptr<Node> theNode1_;

			public:

				// default constructor [6/3/2022 Amir]

				Segment()
				{}

				// constructors [6/3/2022 Amir]

				Segment
				(
					const Standard_Integer theIndex,
					const std::shared_ptr<Node>& theNode0,
					const std::shared_ptr<Node>& theNode1
				)
					: Link(theIndex)
					, theNode0_(theNode0)
					, theNode1_(theNode1)
				{}

				Segment
				(
					const Standard_Integer theIndex,
					std::shared_ptr<Node>&& theNode0,
					std::shared_ptr<Node>&& theNode1
				)
					: Link(theIndex)
					, theNode0_(std::move(theNode0))
					, theNode1_(std::move(theNode1))
				{}


				// override functions and operators [6/3/2022 Amir]

				Standard_Boolean IsSegment() const override
				{
					return Standard_True;
				}

				// public functions and operators [6/3/2022 Amir]

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

				void SetNode0(std::shared_ptr<Node>&& theNode)
				{
					theNode0_ = std::move(theNode);
				}

				void SetNode1(const std::shared_ptr<Node>& theNode)
				{
					theNode1_ = theNode;
				}

				void SetNode1(std::shared_ptr<Node>&& theNode)
				{
					theNode1_ = std::move(theNode);
				}
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_Segment_Header
