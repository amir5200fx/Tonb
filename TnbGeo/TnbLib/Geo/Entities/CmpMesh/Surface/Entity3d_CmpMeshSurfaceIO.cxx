#include <Entity3d_CmpMeshSurface.hxx>

#include <TecPlot.hxx>
#include <GeoIO_VTK.hxx>

void tnbLib::Entity3d_CmpMeshSurface::ExportToPlt(OFstream& theFile) const
{
	Io::ExportMesh(Coords(), Indices(), theFile);
}

void tnbLib::Entity3d_CmpMeshSurface::ExportToVtk(std::fstream& file) const
{
	vtkLib::WriteMesh(*this, "composite mesh", file);
}
