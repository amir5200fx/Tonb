#include <GeoMesh2d_MetricBackground.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::GeoMesh2d_MetricBackground::ExportToPlt(OFstream& File) const
{
	FatalErrorIn(FunctionSIG) <<
		"Not supposed to be called this function." << endl
		<< abort(FatalError);
}