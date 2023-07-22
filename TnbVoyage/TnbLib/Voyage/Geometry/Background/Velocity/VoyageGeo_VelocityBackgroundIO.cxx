#include <VoyageGeo_VelocityBackground.hxx>

#include <GeoMesh2d_Data.hxx>
#include <TecPlot.hxx>

template<>
void tnbLib::VoyageGeo_SingleVelocityBackground::ExportToPlt(OFstream& File) const
{
	if (NOT this->Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh data has been found." << endl
			<< abort(FatalError);
	}
	std::vector<std::array<Standard_Real, 2>> hs;
	hs.reserve(this->Sources().size());
	for (const auto& x : this->Sources())
	{
		std::array<Standard_Real, 2> hi = { x.X(), x.Y() };
		hs.push_back(std::move(hi));
	}
	const auto mesh = this->Mesh()->StaticData();
	Io::ExportField("Velocity", hs, mesh->Points(), mesh->Connectivity(), File);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::VoyageGeo_SingleVelocityBackground);