#include <VoyageMesh_Node.hxx>

#include <VoyageMesh_Edge.hxx>
#include <VoyageMesh_Node.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
Standard_Real 
tnbLib::VoyageMesh_NodeBase::CalcMaxParaAdjLength() const
{
	const auto& edges = RetrieveEdges();
	Standard_Real maxLen = 0;
	for (const auto& x : edges)
	{
		auto edge = x.second.lock();
		Debug_Null_Pointer(edge);

		const std::shared_ptr<VoyageMesh_Node>& n0 = edge->Node0();
		const std::shared_ptr<VoyageMesh_Node>& n1 = edge->Node1();

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto len = n0->Coord().Distance(n1->Coord());
		if (len > maxLen)
		{
			maxLen = len;
		}
	}
	return maxLen;
}