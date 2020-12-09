#include <Marine_Model_ProfileAreaSail.hxx>

tnbLib::marineLib::Model_ProfileAreaSail::Model_ProfileAreaSail
(
	const std::shared_ptr<Geo_ProfileFun>& theArea,
	const std::shared_ptr<Geo_ProfileFun>& theZbar
)
	: theZbar_(theZbar)
	, theArea_(theArea)
{
	// empty body
}

tnbLib::marineLib::Model_ProfileAreaSail::Model_ProfileAreaSail
(
	std::shared_ptr<Geo_ProfileFun>&& theArea, 
	std::shared_ptr<Geo_ProfileFun>&& theZbar
)
	: theArea_(std::move(theArea))
	, theZbar_(std::move(theZbar))
{
	// empty body
}

tnbLib::marineLib::Model_ProfileAreaSail::Model_ProfileAreaSail
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<Geo_ProfileFun>& theArea,
	const std::shared_ptr<Geo_ProfileFun>& theZbar
)
	: theArea_(theArea)
	, theZbar_(theZbar)
	, Model_AreaSail(theIndex, theName)
{
	// empty body
}

tnbLib::marineLib::Model_ProfileAreaSail::Model_ProfileAreaSail
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::shared_ptr<Geo_ProfileFun>&& theArea, 
	std::shared_ptr<Geo_ProfileFun>&& theZbar
)
	: theArea_(std::move(theArea))
	, theZbar_(std::move(theZbar))
	, Model_AreaSail(theIndex, theName)
{
	// empty body
}