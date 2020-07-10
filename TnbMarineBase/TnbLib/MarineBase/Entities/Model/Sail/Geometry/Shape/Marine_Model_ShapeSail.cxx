#include <Marine_Model_ShapeSail.hxx>

tnbLib::marineLib::Model_ShapeSail::Model_ShapeSail
(
	const std::shared_ptr<Body_Sail>& theSail
)
	: theBody_(theSail)
{
}

tnbLib::marineLib::Model_ShapeSail::Model_ShapeSail
(
	std::shared_ptr<Body_Sail>&& theSail
)
	: theBody_(std::move(theSail))
{
}

tnbLib::marineLib::Model_ShapeSail::Model_ShapeSail
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Body_Sail>& theSail
)
	: Marine_GeoSailModel(theIndex)
	, theBody_(theSail)
{
}

tnbLib::marineLib::Model_ShapeSail::Model_ShapeSail
(
	const Standard_Integer theIndex,
	std::shared_ptr<Body_Sail>&& theSail
)
	: Marine_GeoSailModel(theIndex)
	, theBody_(std::move(theSail))
{
}

tnbLib::marineLib::Model_ShapeSail::Model_ShapeSail
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<Body_Sail>& theSail
)
	: Marine_GeoSailModel(theIndex, theName)
	, theBody_(theSail)
{
}

tnbLib::marineLib::Model_ShapeSail::Model_ShapeSail
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::shared_ptr<Body_Sail>&& theSail
)
	: Marine_GeoSailModel(theIndex, theName)
	, theBody_(std::move(theSail))
{
}