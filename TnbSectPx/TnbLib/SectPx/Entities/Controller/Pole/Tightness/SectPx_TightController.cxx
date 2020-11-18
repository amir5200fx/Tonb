#include <SectPx_TightController.hxx>

#include <SectPx_SegmentController.hxx>

Standard_Integer 
tnbLib::SectPx_TightController::NbChildMaps() const
{
	return 2;
}

Standard_Boolean 
tnbLib::SectPx_TightController::HasChildMap() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_TightController::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	return Standard_False;
}

std::shared_ptr<tnbLib::SectPx_Parent> 
tnbLib::SectPx_TightController::ChildMap
(
	const Standard_Integer theIndex
) const
{
	Debug_If_Condition_Message(NOT INSIDE(theIndex, 0, 1), "Invalid index");
	return (&theLeft_)[theIndex];
}

typename tnbLib::sectPxLib::poleControllerType 
tnbLib::SectPx_TightController::PoleType() const
{
	return sectPxLib::poleControllerType::tightness;
}

void tnbLib::SectPx_TightController::RemoveThisFromChildren() const
{
	// empty body
}

void tnbLib::SectPx_TightController::AddThisToChildren() const
{
	// empty body
}

void tnbLib::SectPx_TightController::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	// empty body
}

void tnbLib::SectPx_TightController::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	// empty body
}