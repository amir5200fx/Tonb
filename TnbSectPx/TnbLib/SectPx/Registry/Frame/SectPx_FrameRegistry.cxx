#include <SectPx_FrameRegistry.hxx>

#include <SectPx_RegObj.hxx>
#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <Geo_ItemCounter.hxx>

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