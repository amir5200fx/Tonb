#include <ShapePx_ExtrudedPatch.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::ShapePx_ExtrudedPatch::ShapePx_ExtrudedPatch
(
	const Standard_Integer theIndex,
	const word & theName
)
	: ShapePx_Patch(theIndex, theName)
{
	// empty body
}

tnbLib::ShapePx_ExtrudedPatch::ShapePx_ExtrudedPatch
(
	const std::shared_ptr<ShapePx_Section>& theSect
)
	: ShapePx_Patch(theSect)
{
	// empty body
}

tnbLib::ShapePx_ExtrudedPatch::ShapePx_ExtrudedPatch
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<ShapePx_Section>& theSect
)
	: ShapePx_Patch(theIndex, theName, theSect)
{
	// empty body
}

std::shared_ptr<tnbLib::ShapePx_Profile> 
tnbLib::ShapePx_ExtrudedPatch::RemoveProfile
(
	const Standard_Integer theParIndex
)
{
	auto iter = theParToProfile_.find(theParIndex);
	if (iter NOT_EQUAL theParToProfile_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " the item is not in the tree!" << endl
			<< " - index = " << theParIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theParToProfile_.erase(iter);
	return std::move(item);
}

void tnbLib::ShapePx_ExtrudedPatch::ImportProfileForParameter
(
	const Standard_Integer theParIndex, 
	const std::shared_ptr<ShapePx_Profile>& theProfile
)
{
	auto paired = std::make_pair(theParIndex, theProfile);
	auto insert = theParToProfile_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to insert the profile into the map: duplicate data!" << endl
			<< "- index= " << theParIndex << endl
			<< abort(FatalError);
	}
}

