#include <GeoMesh3d_Background.hxx>

#include <GeoMesh3d_Data.hxx>
#include <TecPlot.hxx>
#include <GeoIO_VTK.hxx>

const std::string tnbLib::GeoMesh3d_Background::extension = ".sbckmsh3d";

template<>
void tnbLib::GeoMesh3d_SingleBackground::ExportToPlt(OFstream& File) const
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

template <>
void tnbLib::GeoMesh3d_SingleBackground::ExportToVtk(OFstream& File) const
{
	if (NOT this->Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh data has been found." << endl
			<< abort(FatalError);
	}
	const auto mesh = this->Mesh()->StaticData();
	std::stringstream stream;
	vtkLib::ExportField(*mesh, this->Sources(), stream);
	File << stream.str();
}

template <>
void tnbLib::GeoMesh3d_SingleBackground::ExportToVtk(std::ostream& os) const
{
	if (NOT this->Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh data has been found." << endl
			<< abort(FatalError);
	}
	const auto mesh = this->Mesh()->StaticData();
	std::stringstream stream;
	vtkLib::ExportField(*mesh, this->Sources(), stream);
	os << stream.str();
}


BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoMesh3d_SingleBackground);