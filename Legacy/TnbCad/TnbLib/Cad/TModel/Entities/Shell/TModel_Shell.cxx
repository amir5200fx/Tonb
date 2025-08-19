#include <TModel_Shell.hxx>

#include <Cad_Tools.hxx>
#include <Entity3d_Box.hxx>
#include <TModel_Surface.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Entity3d_Box 
tnbLib::TModel_Shell::CalcBoundingBox() const
{
	const auto& surfaces = Surfaces();
	if (surfaces.empty())
	{
		FatalErrorIn("Entity3d_Box CalcBoundingBox() const")
			<< "the surface list is empty" << endl
			<< abort(FatalError);
	}

	auto box = Cad_Tools::BoundingBox(surfaces);
	return std::move(box);
}