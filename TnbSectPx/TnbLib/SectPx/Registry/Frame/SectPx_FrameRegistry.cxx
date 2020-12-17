#include <SectPx_FrameRegistry.hxx>

#include <SectPx_RegObj.hxx>
#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_TopoSegment.hxx>
#include <Geo_ItemCounter.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::SectPx_FrameRegistry::CheckObjType
(
	const std::shared_ptr<SectPx_RegObj>& theObj,
	const char * funcName
) const
{
	if (NOT theObj->IsFrameRegObj())
	{
		FatalErrorIn(funcName)
			<< "the object has not valid type" << endl
			<< "type: " << theObj->RegObjTypeName() << endl
			<< abort(FatalError);
	}
}

tnbLib::SectPx_FrameRegistry::SectPx_FrameRegistry
(
	const std::shared_ptr<SectPx_CountRegistry>& theCounter, 
	const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
)
	: SectPx_ObjectRegistry(theCounter, theScatter)
{
	// empty body
}

tnbLib::SectPx_FrameRegistry::SectPx_FrameRegistry
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

Standard_Integer 
tnbLib::SectPx_FrameRegistry::NbTopoSegments() const
{
	Standard_Integer k = 0;
	const auto& segments = Scatter()->ScatterMap(SectPx_RegObjType::topoSegment);
	for (const auto& x : segments)
	{
		Debug_Null_Pointer(x.second.lock());
		auto segment = x.second.lock();
		if (IsContains(segment))
			++k;
	}
	return k;
}

std::vector<std::shared_ptr<tnbLib::SectPx_TopoSegment>> 
tnbLib::SectPx_FrameRegistry::RetrieveTopoSegments() const
{
	std::vector<std::shared_ptr<SectPx_TopoSegment>> segList;
	const auto& segments = Scatter()->ScatterMap(SectPx_RegObjType::topoSegment);
	for (const auto& x : segments)
	{
		Debug_Null_Pointer(x.second.lock());
		auto segment = std::dynamic_pointer_cast<SectPx_TopoSegment>(x.second.lock());
		Debug_Null_Pointer(segment);
		segList.push_back(std::move(segment));
	}
	return std::move(segList);
}