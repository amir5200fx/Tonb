#include <MarineRepairSect_OneEdgeMissSection.hxx>

#include <MarineRepairSect_CrossSegment.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::Pln_Curve>>
tnbLib::MarineRepairSect_OneEdgeMissSection::FillingCurves() const
{
	if (NOT Segment())
	{
		FatalErrorIn(FunctionSIG)
			<< "no segment is loaded!" << endl
			<< abort(FatalError);
	}

	const auto& seg = Segment()->Segment();
	Debug_Null_Pointer(seg);

	const auto& node0 = seg->Node0();
	const auto& node1 = seg->Node1();

	Debug_Null_Pointer(node0);
	Debug_Null_Pointer(node1);

	const auto& vtx0 = node0->Vtx();
	const auto& vtx1 = node1->Vtx();

	Debug_Null_Pointer(vtx0);
	Debug_Null_Pointer(vtx1);

	auto geom = Pln_CurveTools::MakeSegment(vtx0->Coord(), vtx1->Coord());
	Debug_Null_Pointer(geom);

	auto curve = std::make_shared<Pln_Curve>(std::move(geom));
	
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.push_back(std::move(curve));
	return std::move(curves);
}