#include <SectPx_ShapeRegistry.hxx>

#include <SectPx_Par.hxx>
#include <SectPx_RegObj.hxx>
#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <Geo_ItemCounter.hxx>

void tnbLib::SectPx_ShapeRegistry::CheckObjType
(
	const std::shared_ptr<SectPx_RegObj>& theObj,
	const char * funcName
) const
{
	if (NOT theObj->IsShapeRegObj())
	{
		FatalErrorIn(funcName)
			<< "the object has not valid type" << endl
			<< "type: " << theObj->RegObjTypeName() << endl
			<< abort(FatalError);
	}
}

tnbLib::SectPx_ShapeRegistry::SectPx_ShapeRegistry
(
	const std::shared_ptr<SectPx_CountRegistry>& theCounter,
	const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
)
	: SectPx_ObjectRegistry(theCounter, theScatter)
{
	// empty body
}

tnbLib::SectPx_ShapeRegistry::SectPx_ShapeRegistry
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<SectPx_CountRegistry>& theCounter,
	const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
)
	: SectPx_ObjectRegistry(theIndex, theName, theCounter, theScatter)
{
	// empty body
}

std::vector<std::shared_ptr<tnbLib::SectPx_Par>>
tnbLib::SectPx_ShapeRegistry::RetrieveGlobalParameters() const
{
	std::map<Standard_Integer, std::shared_ptr<SectPx_Child>> childMap;
	for (const auto& x : Objects())
	{
		auto parent = std::dynamic_pointer_cast<SectPx_Parent>(x.second);
		if (parent)
		{
			if (parent->HasChildren())
			{
				auto children = parent->RetrieveChildren();
				for (const auto& child : children)
				{
					auto paired = std::make_pair(child->Index(), child);
					auto insert = childMap.insert(std::move(paired));
					if (NOT insert.second)
					{
						// duplicate data
					}
				}
			}
		}
	}
	std::vector<std::shared_ptr<SectPx_Par>> parameters;
	parameters.reserve(childMap.size());
	for (const auto& x : childMap)
	{
		auto par = std::dynamic_pointer_cast<SectPx_Par>(x.second);
		Debug_Null_Pointer(par);
		parameters.push_back(std::move(par));
	}
	return std::move(parameters);
}