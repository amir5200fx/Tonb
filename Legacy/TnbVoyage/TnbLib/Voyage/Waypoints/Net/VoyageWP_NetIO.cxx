#include <VoyageWP_Net.hxx>

#include <Voyage_Tools.hxx>
#include <TecPlot.hxx>

void tnbLib::VoyageWP_Net::ExportToPlt(OFstream& theFile) const
{
	const auto coords = RetrieveCoords();
	const auto ids = RetrieveConnectivity();
	Io::ExportMesh(coords, ids, theFile);
	//Io::ExportMesh(Voyage_Tools::ConvertToVoyageSystem(coords), ids, theFile);
}
