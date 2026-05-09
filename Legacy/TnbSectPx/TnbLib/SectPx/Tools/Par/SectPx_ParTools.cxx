#include <SectPx_ParTools.hxx>

#include <Global_Macros.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_Parent.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean
tnbLib::SectPx_ParTools::HasParent
(
	const std::shared_ptr<SectPx_Child>& theChild
)
{
	return (Standard_Boolean)NbParents(theChild);
}

Standard_Boolean
tnbLib::SectPx_ParTools::IsRemovable
(
	const std::shared_ptr<SectPx_Child>& theChild
)
{
	return NOT HasParent(theChild);
}

Standard_Integer
tnbLib::SectPx_ParTools::NbParents
(
	const std::shared_ptr<SectPx_Child>& theChild
)
{
	Debug_Null_Pointer(theChild);
	return theChild->NbParents();
}

std::map
<
	Standard_Integer,
	std::weak_ptr<tnbLib::SectPx_Parent>
>
tnbLib::SectPx_ParTools::Parents
(
	const std::shared_ptr<SectPx_Child>& theChild
)
{
	Debug_Null_Pointer(theChild);
	std::map
		<
		Standard_Integer,
		std::weak_ptr<tnbLib::SectPx_Parent>
		> parents;
	for (const auto& x : theChild->Parents())
	{
		auto p = x.second.Parent;
		auto paired = std::make_pair(x.first, std::move(p));
		parents.insert(std::move(paired));
	}
	return std::move(parents);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Parent>>
tnbLib::SectPx_ParTools::RetrieveParents
(
	const std::shared_ptr<SectPx_Child>& theChild
)
{
	const auto& parents = theChild->Parents();

	std::vector<std::shared_ptr<SectPx_Parent>> pList;
	pList.reserve(parents.size());
	for (const auto& x : parents)
	{
		Debug_Null_Pointer(x.second.Parent.lock());
		pList.push_back(x.second.Parent.lock());
	}
	return std::move(pList);
}

std::shared_ptr<tnbLib::SectPx_FreePar>
tnbLib::SectPx_ParTools::FreeParameter
(
	const std::shared_ptr<SectPx_RegObj>& theEntity
)
{
	auto freeParam = std::dynamic_pointer_cast<SectPx_FreePar>(theEntity);
	if (NOT freeParam)
	{
		FatalErrorIn
		(
			"std::shared_ptr<SectPx_FreePar> FreeParameter(const std::shared_ptr<SectPx_Entity>& theEntity)"
		)
			<< "the entity is no free!" << endl
			<< abort(FatalError);
	}
	return std::move(freeParam);
}

std::shared_ptr<tnbLib::SectPx_FixedPar>
tnbLib::SectPx_ParTools::FixedParameter
(
	const std::shared_ptr<SectPx_RegObj>& theEntity
)
{
	auto fixedParam = std::dynamic_pointer_cast<SectPx_FixedPar>(theEntity);
	if (NOT fixedParam)
	{
		FatalErrorIn
		(
			"std::shared_ptr<SectPx_FixedPar> FixedParameter(const std::shared_ptr<SectPx_Entity>& theEntity)"
		)
			<< "the entity is not fixed!" << endl
			<< abort(FatalError);
	}
	return std::move(fixedParam);
}

std::shared_ptr<tnbLib::SectPx_ConstPar>
tnbLib::SectPx_ParTools::ConstParameter
(
	const std::shared_ptr<SectPx_RegObj>& theEntity
)
{
	auto constParam = std::dynamic_pointer_cast<SectPx_ConstPar>(theEntity);
	if (NOT constParam)
	{
		FatalErrorIn
		(
			"std::shared_ptr<SectPx_ConstPar> FixedParameter(const std::shared_ptr<SectPx_Entity>& theEntity)"
		)
			<< "the entity is not constant!" << endl
			<< abort(FatalError);
	}
	return std::move(constParam);
}

Standard_Boolean
tnbLib::SectPx_ParTools::IsParameter
(
	const std::shared_ptr<SectPx_RegObj>& theObj
)
{
	auto par = std::dynamic_pointer_cast<SectPx_Par>(theObj);
	if (par) return Standard_True;
	else return Standard_False;
}

void tnbLib::SectPx_ParTools::RemoveParentFromChild
(
	const std::shared_ptr<SectPx_Parent>& theParent,
	const std::shared_ptr<SectPx_Child>& theChild
)
{
	Debug_Null_Pointer(theParent);
	const auto id = theParent->Index();
	const auto& parents = theChild->Parents();

	Debug_Null_Pointer(theChild);
	auto parent = theChild->SelectParent(id);
	if (parent.lock() NOT_EQUAL theParent)
	{
		FatalErrorIn
		(
			"void RemoveParentFromChild(Args...)"
		)
			<< "the parent is not in the tree!" << endl
			<< " index = " << id << endl
			<< abort(FatalError);
	}
	theChild->RemoveFromParents(id);
}

void tnbLib::SectPx_ParTools::AddParentToChild
(
	const std::shared_ptr<SectPx_Parent>& theParent,
	const std::shared_ptr<SectPx_Child>& theChild
)
{
	Debug_Null_Pointer(theParent);
	Debug_Null_Pointer(theChild);

	theChild->ImportToParents(theParent);
}