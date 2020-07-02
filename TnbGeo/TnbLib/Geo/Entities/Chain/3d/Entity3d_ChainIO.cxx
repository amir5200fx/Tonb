#include <Entity3d_Chain.hxx>

#include <TecPlot.hxx>

namespace tnbLib
{

	void Entity3d_Chain::ExportToPlt(OFstream& File) const
	{
		Io::ExportMesh(thePoints_, theConnectivity_, File);
	}
}