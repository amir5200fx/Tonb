#pragma once
#ifndef _Geo3d_ApprxSpaceNode_Header
#define _Geo3d_ApprxSpaceNode_Header

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Geo3d_ApprxSpaceNode
	{

		/*Private Data*/

		Standard_Integer theLevel_;

	protected:

		// default constructor [6/24/2022 Amir]


		// constructors [6/24/2022 Amir]

		explicit Geo3d_ApprxSpaceNode(const Standard_Integer theLev)
			: theLevel_(theLev)
		{}

	public:

		virtual ~Geo3d_ApprxSpaceNode()
		{}


		// public functions and operators [6/24/2022 Amir]

		auto Level() const
		{
			return theLevel_;
		}
	};
}

#endif // !_Geo3d_ApprxSpaceNode_Header
