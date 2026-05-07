#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class NodeType>
inline Standard_Boolean 
tnbLib::Knit_ChainNode<NodeType>::IsLess
(
	const std::shared_ptr<Knit_ChainNode>& theNode0,
	const std::shared_ptr<Knit_ChainNode>& theNode1
)
{
	Debug_Null_Pointer(theNode0);
	Debug_Null_Pointer(theNode1);

	return theNode0->Index() < theNode1->Index();
}