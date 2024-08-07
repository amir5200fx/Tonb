#include <GeoMesh2d_MetricBackground.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const std::string tnbLib::GeoMesh2d_MetricBackground::extension = ".mbckmsh2d";

template<>
void tnbLib::GeoMesh2d_SingleMetricBackground::ExportToPlt(OFstream& File) const
{
	FatalErrorIn(FunctionSIG) <<
		"Not supposed to be called this function." << endl
		<< abort(FatalError);
}

template <>
void tnbLib::GeoMesh2d_SingleMetricBackground::ExportToVtk(OFstream& File) const
{
	FatalErrorIn(FunctionSIG) <<
		"Not supposed to be called this function." << endl
		<< abort(FatalError);
}

template <>
void tnbLib::GeoMesh2d_SingleMetricBackground::ExportToVtk(std::ostream& stream) const
{
	NotImplemented;
}


BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoMesh2d_SingleMetricBackground);