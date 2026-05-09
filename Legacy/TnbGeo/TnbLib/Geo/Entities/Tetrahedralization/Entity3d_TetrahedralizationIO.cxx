#include <Entity3d_Tetrahedralization.hxx>

#include <TecPlot.hxx>

template<>
void tnbLib::Entity3d_Tetrahedralization::ExportToPlt(OFstream& File) const
{
	Io::ExportMesh(this->Points(), this->Connectivity(), File);
}