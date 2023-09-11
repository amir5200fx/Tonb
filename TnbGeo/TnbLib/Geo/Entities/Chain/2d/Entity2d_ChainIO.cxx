#include <Entity2d_Chain.hxx>

#include <TecPlot.hxx>
#include <GeoIO_VTK.hxx>

namespace tnbLib
{
	
	template<>
	void Entity2d_Chain::ExportToPlt(OFstream& File) const
	{
		Io::ExportMesh(thePoints_, theConnectivity_, File);
	}
}

template<>
void tnbLib::Entity2d_Chain::ExportToVtk(OFstream& File) const
{
	vtkLib::WriteMesh(*this, "the Chain", File);
}