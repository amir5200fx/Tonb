#include <Entity3d_QuadMesh.hxx>

#include <TecPlot.hxx>
#include <GeoIO_VTK.hxx>

template <>
void tnbLib::Entity3d_QuadMesh::ExportToPlt(OFstream& File) const
{
	Io::ExportMesh(Points(), Connectivity(), File);
}

template <>
void tnbLib::Entity3d_QuadMesh::ExportToVtk(std::fstream& file) const
{
	vtkLib::WriteMesh(*this, "quadrilateral mesh", file);
}