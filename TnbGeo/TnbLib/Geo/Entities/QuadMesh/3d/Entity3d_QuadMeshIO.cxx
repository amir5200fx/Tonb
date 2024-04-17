#include <Entity3d_QuadMesh.hxx>

#include <TecPlot.hxx>

template <>
void tnbLib::Entity3d_QuadMesh::ExportToPlt(OFstream& File) const
{
	Io::ExportMesh(Points(), Connectivity(), File);
}