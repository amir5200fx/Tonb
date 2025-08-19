#include <SectPx_WeightController.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::WeightController::typeName_("weight");

tnbLib::sectPxLib::WeightController::WeightController
(
	const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
)
	: SectPx_PoleController(theCorner)
{
	//- empty body
}

tnbLib::sectPxLib::WeightController::WeightController
(
	std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
)
	: SectPx_PoleController(std::move(theCorner))
{
	// empty body
}

tnbLib::sectPxLib::WeightController::WeightController
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
)
	: SectPx_PoleController(theIndex, theName, theCorner)
{
	// empty body
}

tnbLib::sectPxLib::WeightController::WeightController
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
)
	: SectPx_PoleController(theIndex, theName, std::move(theCorner))
{
	 //- empty body
}


void tnbLib::sectPxLib::WeightController::SetWeight
(
	const std::shared_ptr<SectPx_Par>& theWeight
)
{
	AddParameterToParent
	(
		theWeight_, theWeight,
		"void SetWeight(const std::shared_ptr<SectPx_Par>&)"
	);
}

tnbLib::word 
tnbLib::sectPxLib::WeightController::RegObjTypeName() const
{
	return typeName_;
}

Standard_Integer 
tnbLib::sectPxLib::WeightController::NbChildren() const
{
	return 1;
}

Standard_Boolean 
tnbLib::sectPxLib::WeightController::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::WeightController::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(Weight(), thePar);
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>> 
tnbLib::sectPxLib::WeightController::RetrieveChildren() const
{
	DefineChildList(children);
	AddParToChildList(Weight(), children);
	return std::move(children);
}

typename tnbLib::sectPxLib::poleControllerType 
tnbLib::sectPxLib::WeightController::PoleType() const
{
	return sectPxLib::poleControllerType::weight;
}

void tnbLib::sectPxLib::WeightController::RemoveThisFromChildren() const
{
	auto xPar = Weight().lock();
	if (xPar)
	{
		RemoveThisFromChild(xPar);
	}
}

void tnbLib::sectPxLib::WeightController::AddThisToChildren() const
{
	auto parent = std::dynamic_pointer_cast<SectPx_Parent>(This());
	Debug_Null_Pointer(parent);

	auto xpar = Weight().lock();
	if (xpar)
	{
		SectPx_ParTools::AddParentToChild(parent, xpar);
	}
}

void tnbLib::sectPxLib::WeightController::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	AddThisParentToChild(thePar);
}

void tnbLib::sectPxLib::WeightController::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}