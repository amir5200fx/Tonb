#include <SectPx_Registry.hxx>

#include <SectPx_RegObj.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_RegObj>
tnbLib::SectPx_Registry::RemoveFromMap
(
	const Standard_Integer theIndex
)
{
	auto iter = theObjects_.find(theIndex);
	if (iter IS_EQUAL theObjects_.end())
	{
		FatalErrorIn
		(
			"std::shared_ptr<SectPx_RegObj> RemoveFromMap(const Standard_Integer theIndex)"
		)
			<< "the object is not in the tree!" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theObjects_.erase(iter);
	return std::move(item);
}

void tnbLib::SectPx_Registry::Add
(
	const Standard_Integer theIndex,
	const std::shared_ptr<SectPx_RegObj>& theObj
)
{
	auto paired = std::make_pair(theIndex, theObj);
	auto insert = theObjects_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn
		(
			"void Add(const Standard_Integer, const std::shared_ptr<SectPx_RegObj>&)"
		)
			<< "duplicate data!" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}
}

void tnbLib::SectPx_Registry::Add
(
	const Standard_Integer theIndex,
	std::shared_ptr<SectPx_RegObj>&& theObj
)
{
	auto paired = std::make_pair(theIndex, std::move(theObj));
	auto insert = theObjects_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn
		(
			"void Add(const Standard_Integer, const std::shared_ptr<SectPx_RegObj>&)"
		)
			<< "duplicate data!" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}
}

Standard_Integer 
tnbLib::SectPx_Registry::Import
(
	const std::shared_ptr<SectPx_RegObj>& theObj
)
{
	const auto id = Counter().RetrieveIndex();

	theObj->SetName(theObj->RegObjTypeName() + " nb. " + std::to_string(id));
	theObj->SetIndex(id);

	Add(id, theObj);
	return id;
}

Standard_Integer 
tnbLib::SectPx_Registry::Import
(
	const word & theName, 
	const std::shared_ptr<SectPx_RegObj>& theObj
)
{
	const auto id = Counter().RetrieveIndex();

	theObj->SetName(theName);
	theObj->SetIndex(id);

	Add(id, theObj);
	return id;
}

Standard_Integer 
tnbLib::SectPx_Registry::Import
(
	std::shared_ptr<SectPx_RegObj>&& theObj
)
{
	const auto id = Counter().RetrieveIndex();

	theObj->SetName(theObj->RegObjTypeName() + " nb. " + std::to_string(id));
	theObj->SetIndex(id);

	Add(id, std::move(theObj));
	return id;
}

Standard_Integer 
tnbLib::SectPx_Registry::Import
(
	const word & theName, 
	std::shared_ptr<SectPx_RegObj>&& theObj
)
{
	const auto id = Counter().RetrieveIndex();

	theObj->SetName(theName);
	theObj->SetIndex(id);

	Add(id, std::move(theObj));
	return id;
}

std::shared_ptr<tnbLib::SectPx_RegObj> 
tnbLib::SectPx_Registry::Remove
(
	const Standard_Integer theIndex
)
{
	auto item = RemoveFromMap(theIndex);

	Counter().ReturnToCounter(theIndex);
	return std::move(item);
}

void tnbLib::SectPx_Registry::Remove
(
	const std::shared_ptr<SectPx_RegObj>& theObj
)
{
#ifdef _DEBUG
	auto selected = SelectObj(theObj->Index());
	if (selected NOT_EQUAL theObj)
	{
		FatalErrorIn
		(
			"void Remove(const std::shared_ptr<SectPx_RegObj>&)"
		)
			<< "the removing item is not in the tree!" << endl
			<< " index = " << theObj->Index() << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	auto item = RemoveFromMap(theObj->Index());
	if (item NOT_EQUAL theObj)
	{
		Add(item->Index(), std::move(item));
		FatalErrorIn
		(
			"void Remove(const std::shared_ptr<SectPx_Phi>& thePar)"
		)
			<< "the removing item is not in the tree!" << endl
			<< " index = " << theObj->Index() << endl
			<< abort(FatalError);
	}

	Counter().ReturnToCounter(theObj->Index());
}

std::shared_ptr<tnbLib::SectPx_RegObj> 
tnbLib::SectPx_Registry::SelectObj
(
	const Standard_Integer theIndex
) const
{
	auto iter = theObjects_.find(theIndex);
	if (iter IS_EQUAL theObjects_.end())
	{
		FatalErrorIn
		(
			"std::shared_ptr<SectPx_RegObj> Select(const Standard_Integer theIndex) const"
		)
			<< "the item is not in the tree!" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}
	return iter->second;
}

std::shared_ptr<tnbLib::SectPx_RegObj> 
tnbLib::SectPx_Registry::Find
(
	const Standard_Integer theIndex
) const
{
	auto iter = theObjects_.find(theIndex);
	if (iter IS_EQUAL theObjects_.end())
	{
		return nullptr;
	}
	return iter->second;
}

void tnbLib::SectPx_Registry::Print
(
	Ostream & out
) const
{
	for (const auto& x : theObjects_)
	{
		Debug_Null_Pointer(x.second);

		const auto& item = x.second;
		out << "- index: " << item->Index()
			<< ", " << getRegObjTypeName(item->RegObjType()) 
			<< "'s name: " 
			<< "[" 
			<< item->Name()
			<< "]"
			<< endl;
	}
}

std::shared_ptr<tnbLib::SectPx_Registry> 
tnbLib::sectPxLib::objRegistry = std::make_shared<tnbLib::SectPx_Registry>(0, "registry");