#pragma once
#ifndef _Geo2d_ApprxSpaceNode_Leaf_Header
#define _Geo2d_ApprxSpaceNode_Leaf_Header

#include <Geo2d_ApprxSpaceNode.hxx>
#include <Entity2d_Box.hxx>

#include <list>

namespace tnbLib
{

	class Geo2d_ApprxSpaceNode_Leaf
		: public Geo2d_ApprxSpaceNode
	{

		/*Private Data*/

		Entity2d_Box theBox_;

		std::list<Geo2d_ApprxSpaceNode_Leaf*> theSNeighbors_;
		std::list<Geo2d_ApprxSpaceNode_Leaf*> theENeighbors_;
		std::list<Geo2d_ApprxSpaceNode_Leaf*> theNNeighbors_;
		std::list<Geo2d_ApprxSpaceNode_Leaf*> theWNeighbors_;

		Geo2d_ApprxSpaceNode* theFather_;

	public:

		Geo2d_ApprxSpaceNode_Leaf(const Standard_Integer theLev, const Entity2d_Box& b)
			: Geo2d_ApprxSpaceNode(theLev)
			, theBox_(b)
		{}


		const auto& Box() const
		{
			return theBox_;
		}

		const auto& SNeighbors() const
		{
			return theSNeighbors_;
		}

		auto& SNeighborsRef()
		{
			return theSNeighbors_;
		}

		const auto& ENeighbors() const
		{
			return theENeighbors_;
		}

		auto& ENeighborsRef()
		{
			return theENeighbors_;
		}

		const auto& NNeighbors() const
		{
			return theNNeighbors_;
		}

		auto& NNeighborsRef()
		{
			return theNNeighbors_;
		}

		const auto& WNeighbors() const
		{
			return theWNeighbors_;
		}

		auto& WNeighborsRef()
		{
			return theWNeighbors_;
		}

		auto Father() const
		{
			return theFather_;
		}

		auto& FatherRef()
		{
			return theFather_;
		}
	};
}

#endif // !_Geo2d_ApprxSpaceNode_Leaf_Header
