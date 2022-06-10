#pragma once
#ifndef _Cad_MergeParaCurves_SuperSegment_Header
#define _Cad_MergeParaCurves_SuperSegment_Header

#include <Cad_MergeParaCurves_SuperLink.hxx>

#include <vector>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			// Forward Declarations [6/4/2022 Amir]

			class SuperNode;
			class Link;

			class SuperSegment
				: public SuperLink
			{

				/*Private Data*/

				std::shared_ptr<SuperNode> theNode0_;
				std::shared_ptr<SuperNode> theNode1_;

				

			public:

				// default constructor [6/4/2022 Amir]

				SuperSegment()
				{}


				// constructors [6/4/2022 Amir]

				SuperSegment
				(
					const Standard_Integer theIndex,
					const std::shared_ptr<SuperNode>& theNode0,
					const std::shared_ptr<SuperNode>& theNode1
				)
					: SuperLink(theIndex)
					, theNode0_(theNode0)
					, theNode1_(theNode1)
				{}

				SuperSegment
				(
					const Standard_Integer theIndex,
					std::shared_ptr<SuperNode>&& theNode0,
					std::shared_ptr<SuperNode>&& theNode1
				)
					: SuperLink(theIndex)
					, theNode0_(std::move(theNode0))
					, theNode1_(std::move(theNode1))
				{}


				// public functions and operators [6/4/2022 Amir]

				const auto& Node0() const
				{
					return theNode0_;
				}

				const auto& Node1() const
				{
					return theNode1_;
				}

				void SetNode0(const std::shared_ptr<SuperNode>& theNode)
				{
					theNode0_ = theNode;
				}

				void SetNode0(std::shared_ptr<SuperNode>&& theNode)
				{
					theNode0_ = std::move(theNode);
				}

				void SetNode1(const std::shared_ptr<SuperNode>& theNode)
				{
					theNode1_ = theNode;
				}

				void SetNode1(std::shared_ptr<SuperNode>&& theNode)
				{
					theNode1_ = std::move(theNode);
				}

			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_SuperSegment_Header
