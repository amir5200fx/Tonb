#include <SectPx_ObjectRegistry.hxx>

#include <SectPx_RegObj.hxx>
#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <Geo_ItemCounter.hxx>

Standard_Integer
tnbLib::SectPx_ObjectRegistry::RetrieveIndex() const
{
	Debug_Null_Pointer(theCounter_);
	return theCounter_->Counter().RetrieveIndex();
}

void tnbLib::SectPx_ObjectRegistry::ReturnToCounter
(
	const Standard_Integer theIndex
)
{
	Debug_Null_Pointer(theCounter_);
	theCounter_->Counter().ReturnToCounter(theIndex);
}

std::shared_ptr<tnbLib::SectPx_RegObj>
tnbLib::SectPx_ObjectRegistry::RemoveFromMap
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

	Debug_Null_Pointer(Scatter());
	Scatter()->RemoveFromScatterMap(item);

	theObjects_.erase(iter);
	return std::move(item);
}

void tnbLib::SectPx_ObjectRegistry::Add
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

	Debug_Null_Pointer(Scatter());
	Scatter()->ImportToScatterMap(theObj);
}

void tnbLib::SectPx_ObjectRegistry::Add
(
	const Standard_Integer theIndex,
	std::shared_ptr<SectPx_RegObj>&& theObj
)
{
	auto obj = std::move(theObj);
	auto paired = std::make_pair(theIndex, obj);
	auto insert = theObjects_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn
		(
			"void Add(const Standard_Integer, std::shared_ptr<SectPx_RegObj>&&)"
		)
			<< "duplicate data!" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(Scatter());
	Scatter()->ImportToScatterMap(obj);
}

tnbLib::SectPx_ObjectRegistry::SectPx_ObjectRegistry
(
	const std::shared_ptr<SectPx_CountRegistry>& theCounter,
	const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
)
	: theCounter_(theCounter)
	, theScatter_(theScatter)
{
	//- empty body
}

tnbLib::SectPx_ObjectRegistry::SectPx_ObjectRegistry
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<SectPx_CountRegistry>& theCounter,
	const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
)
	: SectPx_Entity(theIndex, theName)
	, theCounter_(theCounter)
	, theScatter_(theScatter)
{
	//- empty body
}

Standard_Integer
tnbLib::SectPx_ObjectRegistry::MaxIndex() const
{
	if (theObjects_.empty())
	{
		return 0;
	}
	return (--theObjects_.end())->first;
}

Standard_Integer
tnbLib::SectPx_ObjectRegistry::Import
(
	const std::shared_ptr<SectPx_RegObj>& theObj
)
{
	CheckObjType(theObj, FunctionSIG);

	const auto id = RetrieveIndex();

	theObj->SetName(theObj->RegObjTypeName() + " nb. " + std::to_string(id));
	theObj->SetIndex(id);

	Add(id, theObj);
	return id;
}

Standard_Integer
tnbLib::SectPx_ObjectRegistry::Import
(
	const word & theName,
	const std::shared_ptr<SectPx_RegObj>& theObj
)
{
	CheckObjType(theObj, FunctionSIG);

	const auto id = RetrieveIndex();

	theObj->SetName(theName);
	theObj->SetIndex(id);

	Add(id, theObj);
	return id;
}

Standard_Integer
tnbLib::SectPx_ObjectRegistry::Import
(
	std::shared_ptr<SectPx_RegObj>&& theObj
)
{
	CheckObjType(theObj, FunctionSIG);

	const auto id = RetrieveIndex();

	theObj->SetName(theObj->RegObjTypeName() + " nb. " + std::to_string(id));
	theObj->SetIndex(id);

	Add(id, std::move(theObj));
	return id;
}

Standard_Integer
tnbLib::SectPx_ObjectRegistry::Import
(
	const word & theName,
	std::shared_ptr<SectPx_RegObj>&& theObj
)
{
	CheckObjType(theObj, FunctionSIG);

	const auto id = RetrieveIndex();

	theObj->SetName(theName);
	theObj->SetIndex(id);

	Add(id, std::move(theObj));
	return id;
}

std::shared_ptr<tnbLib::SectPx_RegObj>
tnbLib::SectPx_ObjectRegistry::Remove
(
	const Standard_Integer theIndex
)
{
	auto item = RemoveFromMap(theIndex);

	ReturnToCounter(theIndex);
	return std::move(item);
}

std::shared_ptr<tnbLib::SectPx_RegObj>
tnbLib::SectPx_ObjectRegistry::SelectObj
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
tnbLib::SectPx_ObjectRegistry::Find
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

void tnbLib::SectPx_ObjectRegistry::Remove
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

	ReturnToCounter(theObj->Index());
}

void tnbLib::SectPx_ObjectRegistry::Print(Ostream & out) const
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