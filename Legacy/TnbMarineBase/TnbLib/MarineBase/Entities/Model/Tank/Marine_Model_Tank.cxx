#include <Marine_Model_Tank.hxx>

tnbLib::marineLib::Model_Tank::Model_Tank
(
	const std::shared_ptr<Body_Tank>& theBody
)
	: Marine_Model(0, "tank model")
	, theTank_(theBody)
{
	// empty body
}

tnbLib::marineLib::Model_Tank::Model_Tank
(
	std::shared_ptr<Body_Tank>&& theBody
)
	: Marine_Model(0, "tank model")
	, theTank_(std::move(theBody))
{
	// empty body
}

tnbLib::marineLib::Model_Tank::Model_Tank
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Body_Tank>& theBody
)
	: Marine_Model(theIndex, "tank model")
	, theTank_(theBody)
{
	// empty body
}

tnbLib::marineLib::Model_Tank::Model_Tank
(
	const Standard_Integer theIndex,
	std::shared_ptr<Body_Tank>&& theBody
)
	: Marine_Model(theIndex, "tank model")
	, theTank_(std::move(theBody))
{
	// empty body
}

tnbLib::marineLib::Model_Tank::Model_Tank
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Body_Tank>& theBody
)
	: Marine_Model(theIndex, theName)
	, theTank_(theBody)
{
	// empty body
}

tnbLib::marineLib::Model_Tank::Model_Tank
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::shared_ptr<Body_Tank>&& theBody
)
	: Marine_Model(theIndex, theName)
	, theTank_(std::move(theBody))
{
	// empty body
}