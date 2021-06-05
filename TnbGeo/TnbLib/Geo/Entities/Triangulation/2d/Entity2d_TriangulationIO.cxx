#include <Entity2d_Triangulation.hxx>

#include <TecPlot.hxx>

namespace tnbLib
{

	template<>
	void Entity2d_Triangulation::ExportToPlt(OFstream& File) const
	{
		Io::ExportMesh(Points(), Connectivity(), File);
	}
}