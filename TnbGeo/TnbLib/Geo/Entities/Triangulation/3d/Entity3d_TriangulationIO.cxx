#include <Entity3d_Triangulation.hxx>

#include <TecPlot.hxx>
#include <GeoIO_VTK.hxx>

namespace tnbLib
{

	template<>
	void Entity3d_Triangulation::ExportToPlt(OFstream& File) const
	{
		Io::ExportMesh(Points(), Connectivity(), File);
	}
	template <>
	void Entity3d_Triangulation::ExportToVtk(OFstream& theFile) const
	{
		vtkLib::WriteMesh(*this, "myMesh", theFile);
	}
}