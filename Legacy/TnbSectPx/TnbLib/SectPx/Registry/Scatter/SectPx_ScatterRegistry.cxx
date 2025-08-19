#include <SectPx_ScatterRegistry.hxx>

#include <SectPx_RegObj.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::SectPx_ScatterRegistry::Import
(
	const std::shared_ptr<SectPx_RegObj>& ent, 
	scatterMap & theMap
)
{
	const std::weak_ptr<SectPx_RegObj>& w_ent = ent;
	auto paired = std::make_pair(ent->Index(), w_ent);
	auto insert = theMap.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::SectPx_ScatterRegistry::Remove
(
	const Standard_Integer id,
	scatterMap & theMap
)
{
	auto iter = theMap.find(id);
	if (iter IS_EQUAL theMap.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree" << endl
			<< abort(FatalError);
	}
	theMap.erase(iter);
}

void tnbLib::SectPx_ScatterRegistry::ImportToScatterMap
(
	const std::shared_ptr<SectPx_RegObj>& ent
)
{
	auto& m = theMaps[(size_t)ent->RegObjType()];
	Import(ent, m);
}

void tnbLib::SectPx_ScatterRegistry::RemoveFromScatterMap
(
	const std::shared_ptr<SectPx_RegObj>& ent
)
{
	auto& m = theMaps[(size_t)ent->RegObjType()];
	Remove(ent->Index(), m);
}

Standard_Integer 
tnbLib::SectPx_ScatterRegistry::LastId
(
	SectPx_RegObjType t
) const
{
	const auto& m = ScatterMap(t);
	if (m.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the map is empty!" << endl
			<< abort(FatalError);
	}
	return m.crbegin()->first;
}

const typename tnbLib::SectPx_ScatterRegistry::scatterMap & 
tnbLib::SectPx_ScatterRegistry::ScatterMap
(
	SectPx_RegObjType t
) const
{
	return theMaps[(size_t)t];
}