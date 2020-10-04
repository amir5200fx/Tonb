#include <SectPx_Datum_Compnt.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::Datum_Compnt::typeName_ = "datum_compnt";

tnbLib::word 
tnbLib::sectPxLib::Datum_Compnt::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real 
tnbLib::sectPxLib::Datum_Compnt::xCoord() const
{
	const auto xPtr = X().lock();
	if (NOT xPtr)
	{
		FatalErrorIn("Standard_Real xCoord() const")
			<< "the datum doesn't have x-component!" << endl
			<< abort(FatalError);
	}
	return xPtr->Value();
}

Standard_Real 
tnbLib::sectPxLib::Datum_Compnt::yCoord() const
{
	const auto yPtr = Y().lock();
	if (NOT yPtr)
	{
		FatalErrorIn("Standard_Real yCoord() const")
			<< "the datum doesn't have y-component!" << endl
			<< abort(FatalError);
	}
	return yPtr->Value();
}

Standard_Boolean 
tnbLib::sectPxLib::Datum_Compnt::IsComplete() const
{
	ReturnFalseIfNull(X());
	ReturnFalseIfNull(Y());
	return Standard_True;
}

Standard_Integer 
tnbLib::sectPxLib::Datum_Compnt::NbChildren() const
{
	return 2;
}

Standard_Boolean 
tnbLib::sectPxLib::Datum_Compnt::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::Datum_Compnt::HasChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(X(), thePar);
	ReturnTrueIfParBelongsToThisParent(Y(), thePar);
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>> 
tnbLib::sectPxLib::Datum_Compnt::RetrieveChildren() const
{
	DefineChildList(children);
	AddParToChildList(X(), children);
	AddParToChildList(Y(), children);
	return std::move(children);
}

void tnbLib::sectPxLib::Datum_Compnt::SetX
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

void tnbLib::sectPxLib::Datum_Compnt::SetY
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

void tnbLib::sectPxLib::Datum_Compnt::RemoveThisFromChildren() const
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

void tnbLib::sectPxLib::Datum_Compnt::AddThisToChildren() const
{
	auto parent = std::dynamic_pointer_cast<SectPx_Parent>(This());
	Debug_Null_Pointer(parent);

	auto xpar = X().lock();
	if (xpar)
	{
		SectPx_ParTools::AddParentToChild(parent, xpar);
	}

	auto ypar = Y().lock();
	if (ypar)
	{
		SectPx_ParTools::AddParentToChild(parent, ypar);
	}
}

void tnbLib::sectPxLib::Datum_Compnt::AddThisToChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	AddThisParentToChild(thePar);
}

void tnbLib::sectPxLib::Datum_Compnt::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}