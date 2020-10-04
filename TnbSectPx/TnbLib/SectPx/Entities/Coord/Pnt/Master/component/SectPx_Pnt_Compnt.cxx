#include <SectPx_Pnt_Compnt.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::Pnt_Compnt::typeName_ = "pnt_compnt";

tnbLib::word 
tnbLib::sectPxLib::Pnt_Compnt::RegObjTypeName() const
{
	return typeName_;
}

void tnbLib::sectPxLib::Pnt_Compnt::SetX
(
	const std::shared_ptr<SectPx_Par>& theX
)
{
	AddParameterToParent
	(
		theX_, theX,
		"void SetX(const std::shared_ptr<SectPx_Par>& theX)"
	);
}

void tnbLib::sectPxLib::Pnt_Compnt::SetY
(
	const std::shared_ptr<SectPx_Par>& theY
)
{
	AddParameterToParent
	(
		theY_, theY,
		"void SetY(const std::shared_ptr<SectPx_Par>& theY)"
	);
}

Standard_Real 
tnbLib::sectPxLib::Pnt_Compnt::xCoord() const
{
	const auto xPtr = X().lock();
	if (NOT xPtr)
	{
		FatalErrorIn("Standard_Real xCoord() const")
			<< "the pnt doesn't have x-component!" << endl
			<< abort(FatalError);
	}
	return xPtr->Value();
}

Standard_Real 
tnbLib::sectPxLib::Pnt_Compnt::yCoord() const
{
	const auto yPtr = Y().lock();
	if (NOT yPtr)
	{
		FatalErrorIn("Standard_Real yCoord() const")
			<< "the pnt doesn't have y-component!" << endl
			<< abort(FatalError);
	}
	return yPtr->Value();
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_Compnt::IsComplete() const
{
	ReturnFalseIfNull(X());
	ReturnFalseIfNull(Y());
	return Standard_True;
}

typename tnbLib::sectPxLib::pntType
tnbLib::sectPxLib::Pnt_Compnt::PntType() const
{
	return sectPxLib::pntType::component;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_Compnt::IsComponent() const
{
	return Standard_True;
}

Standard_Integer 
tnbLib::sectPxLib::Pnt_Compnt::NbChildren() const
{
	return 2;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_Compnt::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean
tnbLib::sectPxLib::Pnt_Compnt::HasChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(X(), thePar);
	ReturnTrueIfParBelongsToThisParent(Y(), thePar);
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>> 
tnbLib::sectPxLib::Pnt_Compnt::RetrieveChildren() const
{
	DefineChildList(children);
	AddParToChildList(X(), children);
	AddParToChildList(Y(), children);
	return std::move(children);
}

void tnbLib::sectPxLib::Pnt_Compnt::RemoveThisFromChildren() const
{
	auto xPar = X().lock();
	if (xPar)
	{
		RemoveThisFromChild(xPar);
	}

	auto yPar = Y().lock();
	if (yPar)
	{
		RemoveThisFromChild(yPar);
	}
}

void tnbLib::sectPxLib::Pnt_Compnt::AddThisToChildren() const
{
	AddThisParentToAllChilds(X());
	AddThisParentToAllChilds(Y());
}

void tnbLib::sectPxLib::Pnt_Compnt::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}

void tnbLib::sectPxLib::Pnt_Compnt::AddThisToChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	AddThisParentToChild(thePar);
}
