#pragma once
#ifndef _Knit_ChainNode_Header
#define _Knit_ChainNode_Header

#include <Global_Indexed.hxx>
#include <Knit_ChainNode_Type.hxx>

namespace tnbLib
{

	template<class NodeType>
	class Knit_ChainNode
		: public NodeType
	{

		/*Private Data*/

		Knit_ChainNode_Type theType_;

	public:

		typedef NodeType base;
		typedef typename base::Point Point;

		// default constructor [1/3/2022 Amir]

		Knit_ChainNode()
		{}

		// constructors [1/3/2022 Amir]

		Knit_ChainNode
		(
			const Standard_Integer theIndex, 
			const Point& theCoord
		)
			: base(theIndex, theCoord)
		{}

		Knit_ChainNode
		(
			const Standard_Integer theIndex,
			Point&& theCoord
		)
			: base(theIndex, std::move(theCoord))
		{}


		// public functions and operators [1/3/2022 Amir]

		auto Type() const
		{
			return theType_;
		}

		void SetType(const Knit_ChainNode_Type t)
		{
			theType_ = t;
		}

		static Standard_Boolean IsLess(const std::shared_ptr<Knit_ChainNode>& theNode0, const std::shared_ptr<Knit_ChainNode>& theNode1);
	};
}

#include <Knit_ChainNodeI.hxx>

#endif // !_Knit_ChainNode_Header
