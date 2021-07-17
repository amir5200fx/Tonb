#include <SectPx_CoordAdaptor.hxx>

#include <SectPx_GeoMap.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::SectPx_CoordAdaptor::ImportToGeoMaps
(
	const std::shared_ptr<SectPx_GeoMap>& theMap
)
{
	auto paired = std::make_pair(theMap->Index(), theMap);
	auto insert = theGeoMaps_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected." << endl
			<< " - unable to import the geomap into the tree" << endl
			<< " - index: " << theMap->Index() << endl
			<< abort(FatalError);
	}
}

typename tnbLib::SectPx_CoordAdaptor::mapIter 
tnbLib::SectPx_CoordAdaptor::SelectGeoMap
(
	const Standard_Integer theIndex
)
{
	auto iter = theGeoMaps_.find(theIndex);
	return std::move(iter);
}

std::shared_ptr<tnbLib::SectPx_GeoMap>
tnbLib::SectPx_CoordAdaptor::RemoveGeoMap
(
	const mapIter & theIter
)
{
	if (theIter IS_EQUAL theGeoMaps_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " the geomap is not inside the tree!" << endl
			<< abort(FatalError);
	}
	auto x = theIter->second.lock();
	theGeoMaps_.erase(theIter);
	return std::move(x);
}

std::shared_ptr<tnbLib::SectPx_GeoMap> 
tnbLib::SectPx_CoordAdaptor::RemoveGeoMap
(
	const Standard_Integer theIndex
)
{
	auto iter = theGeoMaps_.find(theIndex);
	if (iter IS_EQUAL theGeoMaps_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " the geomap is not inside the tree!" << endl
			<< " index: " << theIndex << endl
			<< abort(FatalError);
	}
	auto x = iter->second.lock();
	theGeoMaps_.erase(iter);
	return std::move(x);
}