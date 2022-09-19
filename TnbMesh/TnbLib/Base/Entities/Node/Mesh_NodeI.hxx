#pragma once
template<class NodeTraits>
inline Standard_Boolean tnbLib::Mesh_Node<NodeTraits>::IsBoundary() const
{
	return Standard_False;
}

template<class NodeTraits>
Standard_Boolean tnbLib::Mesh_Node<NodeTraits>::IsLess
(
	const std::shared_ptr<Mesh_Node>& theNode0,
	const std::shared_ptr<Mesh_Node>& theNode1
)
{
	Debug_Null_Pointer(theNode0);
	Debug_Null_Pointer(theNode1);

	return theNode0->Index() < theNode1->Index();
}