#include <Marine_Model_Hull.hxx>

tnbLib::marineLib::Model_Hull::Model_Hull
(
	const std::shared_ptr<Body_Displacer>& theBody
)
	: theDisplacer_(theBody)
{
}

tnbLib::marineLib::Model_Hull::Model_Hull
(
	std::shared_ptr<Body_Displacer>&& theBody
)
	: theDisplacer_(std::move(theBody))
{
}

tnbLib::marineLib::Model_Hull::Model_Hull
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Body_Displacer>& theBody
)
	: Marine_Model(theIndex)
	, theDisplacer_(theBody)
{
}

tnbLib::marineLib::Model_Hull::Model_Hull
(
	const Standard_Integer theIndex,
	std::shared_ptr<Body_Displacer>&& theBody
)
	: Marine_Model(theIndex)
	, theDisplacer_(std::move(theBody))
{
}

tnbLib::marineLib::Model_Hull::Model_Hull
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Body_Displacer>& theBody
)
	: Marine_Model(theIndex, theName)
	, theDisplacer_(theBody)
{
}

tnbLib::marineLib::Model_Hull::Model_Hull
(
	const Standard_Integer theIndex,
	const word & theName,
	std::shared_ptr<Body_Displacer>&& theBody
)
	: Marine_Model(theIndex, theName)
	, theDisplacer_(std::move(theBody))
{
}