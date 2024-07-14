#include <Entity3d_CmpMeshSurface.hxx>

#include <TecPlot.hxx>

void tnbLib::Entity3d_CmpMeshSurface::ExportToPlt(OFstream& theFile) const
{
	Io::ExportMesh(Coords(), Indices(), theFile);
}