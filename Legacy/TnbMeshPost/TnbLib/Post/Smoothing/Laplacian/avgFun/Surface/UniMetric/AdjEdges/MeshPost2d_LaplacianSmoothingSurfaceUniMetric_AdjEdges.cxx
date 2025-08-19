#include <MeshPost2d_LaplacianSmoothingSurfaceUniMetric_AdjEdges.hxx>

#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_NodeSurface.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Pnt2d 
tnbLib::MeshPost2d_LaplacianSmoothingSurfaceUniMetric_AdjEdges::CalcAverage
(
	const std::shared_ptr<Aft2d_NodeSurface>& theNode
) const
{
	Debug_Null_Pointer(theNode);
	Debug_Null_Pointer(Metrics());
	Debug_If_Condition(NOT theNode->NbEdges());

	Pnt2d avg(0, 0);

	for (const auto& x : theNode->RetrieveEdges())
	{
		auto e = x.second.lock();
		Debug_Null_Pointer(e);

		const auto& n0 = e->Node0();
		const auto& n1 = e->Node1();

		auto neighbor = n0;
		if (neighbor IS_EQUAL theNode) neighbor = n1;
		Debug_If_Condition(neighbor IS_EQUAL theNode);

		auto dis = Metrics()->CalcUnitDistance(theNode->Coord(), neighbor->Coord());
		Debug_If_Condition_Message(dis <= gp::Resolution(), "zero has been encountered");

		avg += neighbor->Coord() + (1.0 / dis)*(theNode->Coord() - neighbor->Coord());
	}
	return avg / (Standard_Real)theNode->NbEdges();
}