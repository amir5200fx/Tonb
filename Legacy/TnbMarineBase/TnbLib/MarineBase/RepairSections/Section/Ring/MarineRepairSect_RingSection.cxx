#include <MarineRepairSect_RingSection.hxx>

#include <Pln_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::MarineRepairSect_RingSection::FillingCurves() const
{
	const auto& seg = Segment();
	if (NOT seg)
	{
		FatalErrorIn(FunctionSIG)
			<< "no segment has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& edges = seg->Edges();

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(edges.size());
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		curves.push_back(x->Curve());
	}
	return std::move(curves);
}