#include <ShapePx_ExtrudedPatch.hxx>

#include <ShapePx_ContinProfile.hxx>
#include <ShapePx_Profile.hxx>
#include <ShapePx_ParValue.hxx>
#include <SectPx_Limits.hxx>
#include <SectPx_Par.hxx>
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
	const std::shared_ptr<SectPx_Registry>& theRegistry,
	const std::shared_ptr<ShapePx_Section>& theSect
)
	: ShapePx_Patch(theRegistry, theSect)
{
	// empty body
}

tnbLib::ShapePx_ExtrudedPatch::ShapePx_ExtrudedPatch
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<SectPx_Registry>& theRegistry,
	const std::shared_ptr<ShapePx_Section>& theSect
)
	: ShapePx_Patch(theIndex, theName, theRegistry, theSect)
{
	// empty body
}

Standard_Boolean 
tnbLib::ShapePx_ExtrudedPatch::IsExtruded() const
{
	return Standard_True;
}

//Standard_Real
//tnbLib::ShapePx_ExtrudedPatch::MinLower() const
//{
//	Debug_If_Condition(NOT theParToProfile_.size());
//	const auto iter = theParToProfile_.cbegin();
//	return iter->second->MinLower();
//}
//
//Standard_Real
//tnbLib::ShapePx_ExtrudedPatch::MaxUpper() const
//{
//	Debug_If_Condition(NOT theParToProfile_.size());
//	const auto iter = theParToProfile_.cbegin();
//	return iter->second->MaxUpper();
//}

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

std::shared_ptr<tnbLib::ShapePx_ParValue>
tnbLib::ShapePx_ExtrudedPatch::RetrieveParValues
(
	const Standard_Real xi
) const
{
	auto values = std::make_shared<ShapePx_ParValue>();
	Info << "nb of pars: " << theParToProfile_.size() << endl;
	for (const auto& x : theParToProfile_)
	{
		auto cont = std::dynamic_pointer_cast<ShapePx_ContinProfile>(x.second);
		Debug_Null_Pointer(cont);

		auto id = x.first;
		auto val = cont->Value(xi);

		values->SetValue(id, val);
	}
	return std::move(values);
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

void tnbLib::ShapePx_ExtrudedPatch::ImportProfileForParameter
(
	const Standard_Integer theParIndex, 
	std::shared_ptr<ShapePx_Profile>&& theProfile
)
{
	auto paired = std::make_pair(theParIndex, std::move(theProfile));
	auto insert = theParToProfile_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to insert the profile into the map: duplicate data!" << endl
			<< "- index= " << theParIndex << endl
			<< abort(FatalError);
	}
}

void tnbLib::ShapePx_ExtrudedPatch::UpdateProfiles()
{
	for (const auto& x : theParToProfile_)
	{
		x.second->Update();
	}
}