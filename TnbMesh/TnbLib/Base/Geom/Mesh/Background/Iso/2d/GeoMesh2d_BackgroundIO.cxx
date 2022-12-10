#include <GeoMesh2d_Background.hxx>

#include <GeoMesh2d_Data.hxx>
#include <TecPlot.hxx>

template<>
void tnbLib::GeoMesh2d_SingleBackground::ExportToPlt(OFstream& File) const
{
	if (NOT this->Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh data has been found." << endl
			<< abort(FatalError);
	}
	std::vector<std::array<Standard_Real, 1>> hs;
	hs.reserve(this->Sources().size());
	for (auto x : this->Sources())
	{
		std::array<Standard_Real, 1> hi = { x };
		hs.push_back(std::move(hi));
	}
	const auto mesh = this->Mesh()->StaticData();
	Io::ExportField("H", hs, mesh->Points(), mesh->Connectivity(), File);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoMesh2d_SingleBackground);