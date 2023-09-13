#include <VoyageWP_Offset.hxx>

#include <TecPlot.hxx>

void tnbLib::VoyageWP_Offset::ExportToPlt(OFstream& theFile) const
{
	auto nodes = RetrieveNodes();
	std::vector<Pnt2d> coords;
	coords.reserve(nodes.size());
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x);
		coords.emplace_back(x->Coord());
	}
	std::vector<connectivity::triple> ids;
	{
		connectivity::triple t;
		t.Value(0) = 1;
		t.Value(1) = 2;
		t.Value(2) = 1;
		ids.emplace_back(std::move(t));
	}
	for (size_t i = 1; i <= Size() - 2; i++)
	{
		auto i0 = i * 3 - 1;
		auto i1 = i0 + 1;
		auto i2 = i0 + 2;

		auto i3 = (i + 1) * 3 - 1;
		connectivity::triple t0, t1, t2;
		t0.Value(0) = i0;
		t0.Value(1) = i3;
		t0.Value(2) = i0;

		t1.Value(0) = i0;
		t1.Value(1) = i1;
		t1.Value(2) = i0;

		t2.Value(0) = i0;
		t2.Value(1) = i2;
		t2.Value(2) = i0;

		ids.emplace_back(std::move(t0));
		ids.emplace_back(std::move(t1));
		ids.emplace_back(std::move(t2));
	}
	Io::ExportMesh(coords, ids, theFile);
}