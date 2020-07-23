#include <Marine_Model_Hull.hxx>

tnbLib::marineLib::Model_Hull::Model_Hull
(
	const std::shared_ptr<Body_Displacer>& theBody
)
	: Marine_Model(0, "hull model")
	, theDisplacer_(theBody)
{
}

tnbLib::marineLib::Model_Hull::Model_Hull
(
	std::shared_ptr<Body_Displacer>&& theBody
)
	: Marine_Model(0, "hull model")
	, theDisplacer_(std::move(theBody))
{
}

tnbLib::marineLib::Model_Hull::Model_Hull
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Body_Displacer>& theBody
)
	: Marine_Model(theIndex, "hull model")
	, theDisplacer_(theBody)
{
}

tnbLib::marineLib::Model_Hull::Model_Hull
(
	const Standard_Integer theIndex,
	std::shared_ptr<Body_Displacer>&& theBody
)
	: Marine_Model(theIndex, "hull model")
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