#include <MeshBlayer2d_Edge.hxx>

Standard_Boolean 
tnbLib::MeshBLayer2d_Edge::IsBoundary() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::MeshBLayer2d_Edge::IsInner() const
{
	return Standard_False;
}

void tnbLib::MeshBLayer2d_Edge::SetNode0
(
	const std::shared_ptr<MeshBLayer2d_Node>& theNode
)
{
	theNode0_ = theNode;
}

void tnbLib::MeshBLayer2d_Edge::SetNode1
(
	const std::shared_ptr<MeshBLayer2d_Node>& theNode
)
{
	theNode1_ = theNode;
}