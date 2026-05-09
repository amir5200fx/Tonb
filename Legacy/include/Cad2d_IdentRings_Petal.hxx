#pragma once
#ifndef _Cad2d_IdentRings_Petal_Header
#define _Cad2d_IdentRings_Petal_Header

#include <Cad2d_IdentRings_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [2/1/2022 Amir]
	class Pln_Wire;

	namespace cad2dLib
	{

		// Forward Declarations [1/25/2022 Amir]
		class IdentRings_Link;
		class IdentRings_Node;

		class IdentRings_Petal
			: public IdentRings_Entity
		{

			/*Private Data*/

			std::shared_ptr<IdentRings_Node> theNode_;

			std::vector<std::shared_ptr<IdentRings_Link>> theLinks_;

		public:

			// default constructor [1/25/2022 Amir]

			IdentRings_Petal()
			{}


			// constructors [1/25/2022 Amir]

			IdentRings_Petal
			(
				const Standard_Integer theIndex,
				const std::vector<std::shared_ptr<IdentRings_Link>>& theLinks,
				const std::shared_ptr<IdentRings_Node>& theNode
			)
				: IdentRings_Entity(theIndex)
				, theLinks_(theLinks)
				, theNode_(theNode)
			{}

			IdentRings_Petal
			(
				const Standard_Integer theIndex,
				std::vector<std::shared_ptr<IdentRings_Link>>&& theLinks,
				std::shared_ptr<IdentRings_Node>&& theNode
			)
				: IdentRings_Entity(theIndex)
				, theLinks_(std::move(theLinks))
				, theNode_(std::move(theNode))
			{}


			// public functions and operators [1/25/2022 Amir]

			const auto& Node() const
			{
				return theNode_;
			}

			const auto& Links() const
			{
				return theLinks_;
			}

			auto& LinksRef() const
			{
				return theLinks_;
			}

			void SetLinks(const std::vector<std::shared_ptr<IdentRings_Link>>& theLinks)
			{
				theLinks_ = theLinks;
			}

			void SetLinks(std::vector<std::shared_ptr<IdentRings_Link>>&& theLinks)
			{
				theLinks_ = std::move(theLinks);
			}

			void SetNode(const std::shared_ptr<IdentRings_Node>& theNode)
			{
				theNode_ = theNode;
			}

			void SetNode(std::shared_ptr<IdentRings_Node>&& theNode)
			{
				theNode_ = std::move(theNode);
			}

			void Detach();

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Wire> 
				MakeWire
				(
					const std::shared_ptr<cad2dLib::IdentRings_Petal>& thePetal
				);
		};
	}
}

#endif // !_Cad2d_IdentRings_Petal_Header
