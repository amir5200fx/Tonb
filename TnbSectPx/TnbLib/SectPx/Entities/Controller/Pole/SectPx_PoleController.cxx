#include <SectPx_PoleController.hxx>

tnbLib::SectPx_PoleController::SectPx_PoleController
(
	const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
)
	: theCorner_(theCorner)
{
	// empty body
}

tnbLib::SectPx_PoleController::SectPx_PoleController
(
	std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
)
	: theCorner_(std::move(theCorner))
{
	// empty body
}

tnbLib::SectPx_PoleController::SectPx_PoleController
(
	const Standard_Integer theIndex,
	const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
)
	: SectPx_Controller(theIndex)
	, theCorner_(theCorner)
{
	// empty body
}

tnbLib::SectPx_PoleController::SectPx_PoleController
(
	const Standard_Integer theIndex,
	std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
)
	: SectPx_Controller(theIndex)
	, theCorner_(std::move(theCorner))
{
	// empty body
}

tnbLib::SectPx_PoleController::SectPx_PoleController
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
)
	: SectPx_Controller(theIndex, theName)
	, theCorner_(theCorner)
{
	// empty body
}

tnbLib::SectPx_PoleController::SectPx_PoleController
(
	const Standard_Integer theIndex,
	const word & theName,
	std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
)
	: SectPx_Controller(theIndex, theName)
	, theCorner_(std::move(theCorner))
{
	// empty body
}

Standard_Boolean 
tnbLib::SectPx_PoleController::IsOnPole() const
{
	return Standard_True;
}