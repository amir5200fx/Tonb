#include <Entity3d_Hexahedralization.hxx>

#include <TecPlot.hxx>

template <>
void tnbLib::Entity3d_Hexahedralization::ExportToPlt(OFstream& File) const
{
	Io::ExportMesh(this->Points(), this->Connectivity(), File);
}
