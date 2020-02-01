#include <Pln_Edge.hxx>

#include <Entity2d_Polygon.hxx>

void tnbLib::Pln_Edge::ExportToPlt
(
	OFstream & File
) const
{
	if (Mesh())
	{
		Mesh()->ExportToPlt(File);
	}
}