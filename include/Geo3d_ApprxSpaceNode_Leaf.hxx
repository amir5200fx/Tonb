#pragma once
#ifndef _Geo3d_ApprxSpaceNode_Leaf_Header
#define _Geo3d_ApprxSpaceNode_Leaf_Header

#include <Geo3d_ApprxSpaceNode.hxx>
#include <Entity3d_BoxFwd.hxx>

#include <list>
#include <memory>

namespace tnbLib
{

	class Geo3d_ApprxSpaceNode_Leaf
		: public Geo3d_ApprxSpaceNode
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Box> theBox_;

		std::list<Geo3d_ApprxSpaceNode_Leaf*> theSNeighbors_;
		std::list<Geo3d_ApprxSpaceNode_Leaf*> theENeighbors_;
		std::list<Geo3d_ApprxSpaceNode_Leaf*> theNNeighbors_;
		std::list<Geo3d_ApprxSpaceNode_Leaf*> theWNeighbors_;
		std::list<Geo3d_ApprxSpaceNode_Leaf*> theFNeighbors_;
		std::list<Geo3d_ApprxSpaceNode_Leaf*> theBNeighbors_;

		Geo3d_ApprxSpaceNode* theFather_;

	public:

		// default constructor [6/24/2022 Amir]


		// constructors [6/24/2022 Amir]

		Geo3d_ApprxSpaceNode_Leaf
		(
			const Standard_Integer theLev, 
			const std::shared_ptr<Entity3d_Box>& theBox
		)
			: Geo3d_ApprxSpaceNode(theLev)
			, theBox_(theBox)
		{}


		// public functions and operators [6/24/2022 Amir]

		const auto& BoundingBox() const
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

		const auto& NNeighbors() const
		{
			return theNNeighbors_;
		}

		auto& NNeighborsRef()
		{
			return theNNeighbors_;
		}

		const auto& ENeighbors() const
		{
			return theENeighbors_;
		}

		auto& ENeighborsRef()
		{
			return theENeighbors_;
		}

		const auto& WNeighbors() const
		{
			return theWNeighbors_;
		}

		auto& WNeighborsRef()
		{
			return theWNeighbors_;
		}

		const auto& FNeighbors() const
		{
			return theFNeighbors_;
		}

		auto& FNeighborsRef()
		{
			return theFNeighbors_;
		}

		const auto& BNeighbors() const
		{
			return theBNeighbors_;
		}

		auto& BNeighborsRef()
		{
			return theBNeighbors_;
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

#endif // !_Geo3d_ApprxSpaceNode_Leaf_Header
