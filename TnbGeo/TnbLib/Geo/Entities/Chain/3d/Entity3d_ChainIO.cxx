#include "Entity3d_Chain.hxx"

#include <TecPlot.hxx>
#include <GeoIO_VTK.hxx>

namespace tnbLib
{

	void Entity3d_Chain::ExportToPlt(OFstream& File) const
	{
		Io::ExportMesh(thePoints_, theConnectivity_, File);
	}

	void Entity3d_Chain::ExportToVtk(std::fstream& file) const
	{
		vtkLib::WriteMesh(*this, "the chain", file);
	}
}