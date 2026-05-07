#include <SectPx_ParRegistry.hxx>

#include <SectPx_RegObj.hxx>
#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <Geo_ItemCounter.hxx>

void tnbLib::SectPx_ParRegistry::CheckObjType
(
	const std::shared_ptr<SectPx_RegObj>& theObj,
	const char * funcName
) const
{
	if (NOT theObj->IsParRegObj())
	{
		FatalErrorIn(funcName)
			<< "the object has not valid type" << endl
			<< "type: " << theObj->RegObjTypeName() << endl
			<< abort(FatalError);
	}
}

tnbLib::SectPx_ParRegistry::SectPx_ParRegistry
(
	const std::shared_ptr<SectPx_CountRegistry>& theCounter,
	const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
)
	: SectPx_ObjectRegistry(theCounter, theScatter)
{
	// empty body
}

tnbLib::SectPx_ParRegistry::SectPx_ParRegistry
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