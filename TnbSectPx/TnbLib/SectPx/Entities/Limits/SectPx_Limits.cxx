#include <SectPx_Limits.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::SectPx_Limits::typeName_ = "limits";

tnbLib::SectPx_Limits::SectPx_Limits
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: SectPx_Parent(theIndex, theName)
{
	// empty body
}

void tnbLib::SectPx_Limits::SetStart(const std::shared_ptr<SectPx_Par>& thePar)
{
	AddParameterToParent(theStart_, thePar, FunctionSIG);
}

void tnbLib::SectPx_Limits::SetEnd(const std::shared_ptr<SectPx_Par>& thePar)
{
	AddParameterToParent(theEnd_, thePar, FunctionSIG);
}

Standard_Real 
tnbLib::SectPx_Limits::Lower() const
{
	Debug_Null_Pointer(Start().lock());
	return Start().lock()->Value();
}

Standard_Real 
tnbLib::SectPx_Limits::Upper() const
{
	Debug_Null_Pointer(End().lock());
	return End().lock()->Value();
}

tnbLib::word 
tnbLib::SectPx_Limits::RegObjTypeName() const
{
	return typeName_;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Limits::RegObjType() const
{
	return sectPxLib::regObjType();
}

Standard_Integer 
tnbLib::SectPx_Limits::NbChildren() const
{
	return 2;
}

Standard_Boolean 
tnbLib::SectPx_Limits::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_Limits::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(Start(), thePar);
	ReturnTrueIfParBelongsToThisParent(End(), thePar);

	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>> 
tnbLib::SectPx_Limits::RetrieveChildren() const
{
	DefineChildList(children);
	AddParToChildList(Start(), children);
	AddParToChildList(End(), children);

	return std::move(children);
}

void tnbLib::SectPx_Limits::RemoveThisFromChildren() const
{
	auto sPar = Start().lock();
	if (sPar)
	{
		RemoveThisFromChild(sPar);
	}

	auto ePar = End().lock();
	if (ePar)
	{
		RemoveThisFromChild(ePar);
	}
}

void tnbLib::SectPx_Limits::AddThisToChildren() const
{
	AddThisParentToChildren(Start());
	AddThisParentToChildren(End());
}

void tnbLib::SectPx_Limits::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}

void tnbLib::SectPx_Limits::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	AddThisParentToChild(thePar);
}