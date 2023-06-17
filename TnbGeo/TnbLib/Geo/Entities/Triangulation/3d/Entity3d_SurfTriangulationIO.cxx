#include <Entity3d_SurfTriangulation.hxx>

#include <TecPlot.hxx>

template<>
void tnbLib::Entity3d_SurfTriangulation::ExportToPlt(OFstream& File) const
{
	const auto coords = RetrieveCoords(Points());
	Io::ExportMesh(coords, Connectivity(), File);
}