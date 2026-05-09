#include <Cad_GModel.hxx>

#include <Cad_Tools.hxx>
#include <Cad_Shape.hxx>
#include <GModel_Surface.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const std::string tnbLib::Cad_GModel::extension = ".gmodel";

void tnbLib::Cad_GModel::SetFaces()
{
	if (NOT Shape())
	{
		FatalErrorIn(FunctionSIG)
			<< "no shape has been found." << endl
			<< abort(FatalError);
	}

	const auto& surfaces = Surfaces();
	auto faces = Cad_Tools::RetrieveFaces(Shape()->Shape());
	if (surfaces.size() NOT_EQUAL faces.size())
	{
		FatalErrorIn(FunctionSIG)
			<< "the nb. of surfaces and the nb. of faces are not compatible." << endl
			<< abort(FatalError);
	}

	Standard_Integer k = 0;
	for (const auto& x : faces)
	{
		Debug_Null_Pointer(surfaces.at(k));
		surfaces.at(k++)->SetFace(x);
	}
}