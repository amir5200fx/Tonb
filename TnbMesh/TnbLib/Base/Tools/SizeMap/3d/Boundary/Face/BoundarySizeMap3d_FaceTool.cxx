#include <BoundarySizeMap3d_FaceTool.hxx>

#include <Cad_TModel.hxx>
#include <TModel_Surface.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::BoundarySizeMap3d_FaceTool::DEFAULT_MAX_NB_CORR_ITERS(3);

std::vector<std::shared_ptr<tnbLib::TModel_Surface>> 
tnbLib::BoundarySizeMap3d_FaceTool::RetrieveFaces() const
{
	std::vector<std::shared_ptr<TModel_Surface>> items;
	RetrieveFacesTo(items);

	return std::move(items);
}

void tnbLib::BoundarySizeMap3d_FaceTool::RetrieveFacesTo
(
	std::vector<std::shared_ptr<TModel_Surface>>& theItems
) const
{
	if (NOT Model())
	{
		FatalErrorIn(FunctionSIG)
			<< "no model has been found." << endl
			<< abort(FatalError);
	}

	if (NOT Model()->Faces())
	{
		FatalErrorIn(FunctionSIG)
			<< "no face manager has been found." << endl
			<< abort(FatalError);
	}
	const auto& manager = *Model()->Faces();
	for (const auto& x : Patches())
	{
		if (NOT manager.HasBlock(x))
		{
			FatalErrorIn(FunctionSIG)
				<< "the face manager doesn't have such a block." << endl
				<< " - block name: " << x << endl
				<< abort(FatalError);
		}
		auto block = manager.SelectBlock(x);
		const auto& entities = block->second;
		for (const auto& e : entities->Entities())
		{
			Debug_Null_Pointer(e.second);
			theItems.push_back(e.second);
		}
	}
}