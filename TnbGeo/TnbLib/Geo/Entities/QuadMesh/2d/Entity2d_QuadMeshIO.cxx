#include <Entity2d_QuadMesh.hxx>

#include <TecPlot.hxx>

template <>
void tnbLib::Entity2d_QuadMesh::ExportToPlt(OFstream& File) const
{
	Io::ExportMesh(Points(), Connectivity(), File);
}
