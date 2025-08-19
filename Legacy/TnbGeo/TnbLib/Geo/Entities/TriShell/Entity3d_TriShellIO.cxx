#include <Entity3d_TriShell.hxx>

#include <TecPlot.hxx>

void tnbLib::Entity3d_TriShell::ExportToPlt(OFstream& theFile) const
{
	Io::ExportMesh(theCoords_, theElements_, theFile);
}