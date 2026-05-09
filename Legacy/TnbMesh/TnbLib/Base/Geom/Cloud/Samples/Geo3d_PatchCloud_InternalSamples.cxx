#include <Geo3d_PatchCloud_InternalSamples.hxx>

#include <Geo3d_PatchCloud_TriSamples.hxx>
#include <Geo3d_PatchCloud_EdgeSamples.hxx>
#include <Geo_GraphTools.hxx>
#include <Geo2d_Graph.hxx>
#include <Geo2d_GraphEdge.hxx>
#include <Geo2d_SegmentGraphEdge.hxx>
#include <Geo2d_GraphNode.hxx>
#include <Entity2d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<tnbLib::Pnt2d> 
tnbLib::Geo3d_PatchCloud_InternalSamples::CalcCloud
(
	const Entity2d_Triangulation & theTris
) const
{
	std::vector<Pnt2d> coords;

	if (EdgeSamples())
	{
		auto graph = Geo_GraphTools::GetGraph(theTris);
		const auto& samples = EdgeSamples();

		const auto& edges = graph->Edges();
		for (const auto& x : edges)
		{
			const auto& edge = x.second;
			Debug_Null_Pointer(edge);

			auto seg = std::dynamic_pointer_cast<Geo2d_SegmentGraphEdge>(edge);
			Debug_If_Condition_Message(NOT edge, "the invalid mesh has been detected.");

			const auto& n0 = seg->Node0();
			const auto& n1 = seg->Node1();
			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			const auto& p0 = n0->Coord();
			const auto& p1 = n1->Coord();

			auto internals = samples->CalcSamples(p0, p1);
			for (auto& p : internals)
			{
				coords.push_back(std::move(p));
			}
		}
	}

	if (TriSamples())
	{
		const auto& samples = TriSamples();
		const auto& pts = theTris.Points();
		for (const auto& ids : theTris.Connectivity())
		{
			auto i0 = Index_Of(ids.Value(0));
			auto i1 = Index_Of(ids.Value(1));
			auto i2 = Index_Of(ids.Value(2));

			const auto& p0 = pts.at(i0);
			const auto& p1 = pts.at(i1);
			const auto& p2 = pts.at(i2);

			auto internals = samples->CalcSamples(p0, p1, p2);
			for (auto& p : internals)
			{
				coords.push_back(std::move(p));
			}
		}
	}

	const auto& pts = theTris.Points();
	for (const auto& p : pts)
	{
		coords.push_back(p);
	}
	return std::move(coords);
}