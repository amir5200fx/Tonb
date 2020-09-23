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