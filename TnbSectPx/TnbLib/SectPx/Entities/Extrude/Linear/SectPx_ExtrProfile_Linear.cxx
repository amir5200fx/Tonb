#include <SectPx_ExtrProfile_Linear.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::ExtrProfile_Linear::typeName_("extrProfile_linear");
const short tnbLib::sectPxLib::ExtrProfile_Linear::nbPoints_ = 2;

tnbLib::sectPxLib::ExtrProfile_Linear::ExtrProfile_Linear
(
	const Standard_Integer theIndex
)
	: SectPx_ExtrProfile(theIndex)
{
	// empty body
}

tnbLib::sectPxLib::ExtrProfile_Linear::ExtrProfile_Linear
(
	const Standard_Integer theIndex,
	const word & theName
)
	: SectPx_ExtrProfile(theIndex, theName)
{
	// empty body
}

void tnbLib::sectPxLib::ExtrProfile_Linear::SetX0
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX0_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_Linear::SetX1
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX1_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_Linear::SetValue0
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue0_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_Linear::SetValue1
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue1_, thePar, FunctionSIG);
}

Standard_Real
tnbLib::sectPxLib::ExtrProfile_Linear::MinLower() const
{
	Debug_Null_Pointer(X0().lock());
	return X0().lock()->Value();
}

Standard_Real
tnbLib::sectPxLib::ExtrProfile_Linear::MaxUpper() const
{
	Debug_Null_Pointer(X1().lock());
	return X1().lock()->Value();
}

Standard_Integer
tnbLib::sectPxLib::ExtrProfile_Linear::NbPoints() const
{
	return (Standard_Integer)nbPoints_;
}

tnbLib::Pnt2d
tnbLib::sectPxLib::ExtrProfile_Linear::Point
(
	const Standard_Integer theIndex
) const
{
	Debug_If_Condition_Message(NOT INSIDE(theIndex, 0, NbPoints() - 1), "the index has been exceed the boundaies");
	const auto& x = (&theX0_)[theIndex];
	const auto& y = (&theValue0_)[theIndex];

	Pnt2d pt(x.lock()->Value(), y.lock()->Value());
	return std::move(pt);
}

Standard_Integer
tnbLib::sectPxLib::ExtrProfile_Linear::NbChildren() const
{
	return Standard_Integer(6);
}

Standard_Boolean
tnbLib::sectPxLib::ExtrProfile_Linear::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean
tnbLib::sectPxLib::ExtrProfile_Linear::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(X0(), thePar);
	ReturnTrueIfParBelongsToThisParent(X1(), thePar);
	ReturnTrueIfParBelongsToThisParent(Value0(), thePar);
	ReturnTrueIfParBelongsToThisParent(Value1(), thePar);

	ReturnTrueIfParBelongsToThisParent(Start(), thePar);
	ReturnTrueIfParBelongsToThisParent(End(), thePar);
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>>
tnbLib::sectPxLib::ExtrProfile_Linear::RetrieveChildren() const
{
	DefineChildList(children);
	AddParToChildList(X0(), children);
	AddParToChildList(X1(), children);
	AddParToChildList(Value0(), children);
	AddParToChildList(Value1(), children);

	AddParToChildList(Start(), children);
	AddParToChildList(End(), children);
	return std::move(children);
}

void tnbLib::sectPxLib::ExtrProfile_Linear::RemoveThisFromChildren() const
{
	auto x0Par = X0().lock();
	if (x0Par)
	{
		RemoveThisFromChild(x0Par);
	}

	auto x1Par = X1().lock();
	if (x1Par)
	{
		RemoveThisFromChild(x1Par);
	}

	auto v0Par = Value0().lock();
	if (v0Par)
	{
		RemoveThisFromChild(v0Par);
	}

	auto v1Par = Value0().lock();
	if (v1Par)
	{
		RemoveThisFromChild(v1Par);
	}

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

void tnbLib::sectPxLib::ExtrProfile_Linear::AddThisToChildren() const
{
	AddThisParentToChildren(X0());
	AddThisParentToChildren(X1());
	AddThisParentToChildren(Value0());
	AddThisParentToChildren(Value1());

	AddThisParentToChildren(Start());
	AddThisParentToChildren(End());
}

void tnbLib::sectPxLib::ExtrProfile_Linear::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}

void tnbLib::sectPxLib::ExtrProfile_Linear::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	AddThisParentToChild(thePar);
}