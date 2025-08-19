#pragma once
#ifndef _Geo2d_ApprxSpaceNode_Internal_Header
#define _Geo2d_ApprxSpaceNode_Internal_Header

#include <Geo2d_ApprxSpaceNode.hxx>

namespace tnbLib
{

	class Geo2d_ApprxSpaceNode_Internal
		: public Geo2d_ApprxSpaceNode
	{

		/* Private Data*/

		Geo2d_ApprxSpaceNode* theSw_;
		Geo2d_ApprxSpaceNode* theSe_;
		Geo2d_ApprxSpaceNode* theNw_;
		Geo2d_ApprxSpaceNode* theNe_;


	public:


		Geo2d_ApprxSpaceNode_Internal(const Standard_Integer theLev)
			: Geo2d_ApprxSpaceNode(theLev)
			, theNe_(0)
			, theNw_(0)
			, theSe_(0)
			, theSw_(0)
		{}


		//- public functions and operators

		auto Sw() const
		{
			return theSw_;
		}

		auto& SwRef()
		{
			return theSw_;
		}

		auto Se() const
		{
			return theSe_;
		}

		auto& SeRef()
		{
			return theSe_;
		}

		auto Nw() const
		{
			return theNw_;
		}

		auto& NwRef()
		{
			return theNw_;
		}

		auto Ne() const
		{
			return theNe_;
		}

		auto& NeRef()
		{
			return theNe_;
		}

	};
}

#endif // !_Geo2d_ApprxSpaceNode_Internal_Header
