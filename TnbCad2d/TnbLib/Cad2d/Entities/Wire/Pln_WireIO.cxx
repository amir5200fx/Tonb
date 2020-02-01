#include <Pln_Wire.hxx>

#include <Pln_CmpEdge.hxx>

void tnbLib::Pln_Wire::ExportToPlt(OFstream & File) const
{
	if (CmpEdge())
	{
		CmpEdge()->ExportToPlt(File);
	}
}