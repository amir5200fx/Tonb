#pragma once
#ifndef _Cad2d_IdentRings_Ring_Header
#define _Cad2d_IdentRings_Ring_Header

#include <Cad2d_IdentRings_Link.hxx>

namespace tnbLib
{

	namespace cad2dLib
	{

		class IdentRings_Ring
			: public IdentRings_Link
		{

			/*Private Data*/

			std::shared_ptr<IdentRings_Node> theNode_;

		public:

			// default constructor [1/24/2022 Amir]

			IdentRings_Ring()
			{}

			// constructors [1/24/2022 Amir]

			IdentRings_Ring
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<IdentRings_Node>& theNode,
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			)
				: IdentRings_Link(theIndex, theEdges)
				, theNode_(theNode)
			{}

			IdentRings_Ring
			(
				const Standard_Integer theIndex,
				std::shared_ptr<IdentRings_Node>&& theNode,
				std::vector<std::shared_ptr<Pln_Edge>>&& theEdges
			)
				: IdentRings_Link(theIndex, std::move(theEdges))
				, theNode_(std::move(theNode))
			{}

			// override functions and operators [1/24/2022 Amir]

			Standard_Boolean IsRing() const override
			{
				return Standard_True;
			}

			TnbCad2d_EXPORT void Attach() override;
			TnbCad2d_EXPORT void Detach() override;

			// public functions and operators [1/24/2022 Amir]

			const auto& Node() const
			{
				return theNode_;
			}

			void SetNode(const std::shared_ptr<IdentRings_Node>& theNode)
			{
				theNode_ = theNode;
			}

			void SetNode(std::shared_ptr<IdentRings_Node>&& theNode)
			{
				theNode_ = std::move(theNode);
			}
		};
	}
}

#endif // !_Cad2d_IdentRings_Ring_Header
