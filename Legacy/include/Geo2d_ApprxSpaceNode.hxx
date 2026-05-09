#pragma once
#ifndef _Geo2d_ApprxSpaceNode_Header
#define _Geo2d_ApprxSpaceNode_Header

#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Geo2d_ApprxSpaceNode
	{

		/* Private Data*/

		Standard_Integer theLevel_;
		

	protected:

		Geo2d_ApprxSpaceNode(const Standard_Integer theLev)
			: theLevel_(theLev)
		{}

	public:

		virtual ~Geo2d_ApprxSpaceNode()
		{}


		auto Level() const
		{
			return theLevel_;
		}

	};
}

#endif // !_Geo2d_ApprxSpaceNode_Header
