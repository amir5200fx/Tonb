#include <ShipModeler_Basic_Volume.hxx>

tnbLib::shipModelerLib::Basic_Volume::Basic_Volume
(
	const std::shared_ptr<Marine_Body>& theBody
)
	: theBody_(theBody)
{
}

tnbLib::shipModelerLib::Basic_Volume::Basic_Volume
(
	const std::shared_ptr<Marine_Body>&& theBody
)
	: theBody_(std::move(theBody))
{
}

tnbLib::shipModelerLib::Basic_Volume::Basic_Volume
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Marine_Body>& theBody
)
	: Basic_Entity(theIndex)
	, theBody_(theBody)
{
}

tnbLib::shipModelerLib::Basic_Volume::Basic_Volume
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Marine_Body>&& theBody
)
	: Basic_Entity(theIndex)
	, theBody_(std::move(theBody))
{
}

tnbLib::shipModelerLib::Basic_Volume::Basic_Volume
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Marine_Body>& theBody
)
	: Basic_Entity(theIndex, theName)
	, theBody_(theBody)
{
}

tnbLib::shipModelerLib::Basic_Volume::Basic_Volume
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Marine_Body>&& theBody
)
	: Basic_Entity(theIndex, theName)
	, theBody_(std::move(theBody))
{
}