#include <Marine_Model_BodySail.hxx>

tnbLib::marineLib::Model_BodySail::Model_BodySail
(
	const std::shared_ptr<Body_Sail>& theSail
)
	: theBody_(theSail)
{
}

tnbLib::marineLib::Model_BodySail::Model_BodySail
(
	std::shared_ptr<Body_Sail>&& theSail
)
	: theBody_(std::move(theSail))
{
}

tnbLib::marineLib::Model_BodySail::Model_BodySail
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Body_Sail>& theSail
)
	: Model_GeoSail(theIndex)
	, theBody_(theSail)
{
}

tnbLib::marineLib::Model_BodySail::Model_BodySail
(
	const Standard_Integer theIndex,
	std::shared_ptr<Body_Sail>&& theSail
)
	: Model_GeoSail(theIndex)
	, theBody_(std::move(theSail))
{
}

tnbLib::marineLib::Model_BodySail::Model_BodySail
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<Body_Sail>& theSail
)
	: Model_GeoSail(theIndex, theName)
	, theBody_(theSail)
{
}

tnbLib::marineLib::Model_BodySail::Model_BodySail
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::shared_ptr<Body_Sail>&& theSail
)
	: Model_GeoSail(theIndex, theName)
	, theBody_(std::move(theSail))
{
}