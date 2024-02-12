#include <Entity2d_Triangulation.hxx>

#include <TecPlot.hxx>
#include <GeoIO_VTK.hxx>

namespace tnbLib
{

	template<>
	void Entity2d_Triangulation::ExportToPlt(OFstream& File) const
	{
		Io::ExportMesh(Points(), Connectivity(), File);
	}
}

template <>
void tnbLib::Entity2d_Triangulation::StreamToPlt(std::stringstream& theStream) const
{
	Io::ExportMesh(Points(), Connectivity(), theStream);
}

template<>
void tnbLib::Entity2d_Triangulation::ExportToVtk(OFstream& theFile) const
{
	vtkLib::WriteMesh(*this, "The triangular mesh", theFile);
}

template <>
void tnbLib::Entity2d_Triangulation::ExportToVtk(std::stringstream& theStream) const
{
	vtkLib::WriteMesh(*this, "The triangular mesh", theStream);
}