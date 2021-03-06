#include <TModel_Shell.hxx>

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

	auto iter = surfaces.begin();

	Debug_Null_Pointer((*iter));
	auto box = (*iter)->BoundingBox();

	iter++;

	while (iter NOT_EQUAL surfaces.end())
	{
		Debug_Null_Pointer((*iter));
		box = Entity3d_Box::Union(box, (*iter)->BoundingBox());

		iter++;
	}
	return std::move(box);
}