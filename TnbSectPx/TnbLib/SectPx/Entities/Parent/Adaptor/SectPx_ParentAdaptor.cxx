#include <SectPx_ParentAdaptor.hxx>

#include <SectPx_Parent.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::SectPx_ParentAdaptor::Add
(
	const Standard_Integer theIndex,
	const std::shared_ptr<SectPx_Parent>& theParent
)
{
	if (theIndex <= 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "attempting to import unregistered parent into the list!" << endl
			<< abort(FatalError);
	}
	Debug_Null_Pointer(theParent);

	auto iter = theParents_.find(theIndex);
	if (iter IS_EQUAL theParents_.end())
	{
		auto parent = Pair(theParent);
		auto paired = std::make_pair(theIndex, std::move(parent));
		auto insert = theParents_.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn
			(
				"void Add(const Standard_Integer theIndex, const std::shared_ptr<SectPx_Parent>& theParent)"
			)
				<< "something went wrong: unable to insert the item to the tree" << endl
				<< " index = " << theIndex << endl
				<< abort(FatalError);
		}
	}
	else
	{
		Debug_Null_Pointer(iter->second.Parent.lock());

#ifdef _DEBUG
		if (iter->second.Parent.lock() NOT_EQUAL theParent)
		{
			FatalErrorIn(FunctionSIG)
				<< "the condition is not satisfied!" << endl
				<< " parent index: " << theParent->Index() << endl
				<< " registered parent index: " << iter->second.Parent.lock()->Index() << endl
				<< abort(FatalError);
		}
#endif // _DEBUG

		//Debug_If_Condition(iter->second.Parent.lock() NOT_EQUAL theParent);
		auto& parent = iter->second;
		parent.K++;
	}
	
}

std::weak_ptr<tnbLib::SectPx_Parent>
tnbLib::SectPx_ParentAdaptor::SelectParent
(
	const Standard_Integer theIndex
)
{
	auto iter = theParents_.find(theIndex);
	if (iter IS_EQUAL theParents_.end())
	{
		FatalErrorIn
		(
			"std::weak_ptr<SectPx_Parent> SelectParent(const Standard_Integer theIndex)"
		)
			<< "the parent is not int the tree!" << endl
			<< abort(FatalError);
	}
	Debug_If_Condition(NOT iter->second.K);
	return iter->second.Parent;
}

std::weak_ptr<tnbLib::SectPx_Parent>
tnbLib::SectPx_ParentAdaptor::RemoveFromParents
(
	const Standard_Integer theIndex
)
{
	auto iter = theParents_.find(theIndex);
	if (iter IS_EQUAL theParents_.end())
	{
		FatalErrorIn
		(
			"std::weak_ptr<SectPx_Parent> RemoveFromParents(const Standard_Integer theIndex)"
		)
			<< "the parent is not int the tree!" << endl
			<< abort(FatalError);
	}

	iter->second.K--;
	if (iter->second.K <= 0)
	{
		auto item = std::move(iter->second.Parent);
		theParents_.erase(iter);
		return std::move(item);
	}
	return iter->second.Parent;
}

#include <SectPx_Parent.hxx>

void tnbLib::SectPx_ParentAdaptor::ImportToParents
(
	const std::shared_ptr<SectPx_Parent>& theParent
)
{
	Add(theParent->Index(), theParent);
}

Standard_Boolean 
tnbLib::SectPx_ParentAdaptor::HasThisParent
(
	const std::shared_ptr<SectPx_Parent>& theParent
) const
{
	auto id = theParent->Index();
	auto iter = theParents_.find(id);
	if (iter IS_EQUAL theParents_.end())
	{
		return Standard_False;
	}

#ifdef _DEBUG
	auto x = iter->second.Parent.lock();
	if (x NOT_EQUAL theParent)
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data has been detected!" << endl
			<< " - two different parents have the same id!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	return Standard_True;
}