#include <Pln_CmpEdge.hxx>

#include <Pln_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Pln_CmpEdge::ExportToPlt(OFstream & File) const
{
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		x->ExportToPlt(File);
	}
}

DECLARE_SAVE_IMP(tnbLib::Pln_CmpEdge)
{
	ar & Edges();
}

DECLARE_LOAD_IMP(tnbLib::Pln_CmpEdge)
{
	ar & ChangeEdges();
}