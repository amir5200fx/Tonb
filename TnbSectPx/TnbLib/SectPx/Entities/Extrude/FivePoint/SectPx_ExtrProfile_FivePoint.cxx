#include <SectPx_ExtrProfile_FivePoint.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::ExtrProfile_FivePoint::typeName_("extrProfile_fivePoint");
const short tnbLib::sectPxLib::ExtrProfile_FivePoint::nbPoints_ = 5;

tnbLib::sectPxLib::ExtrProfile_FivePoint::ExtrProfile_FivePoint
(
	const Standard_Integer theIndex
)
	: SectPx_ExtrProfile(theIndex)
{
	// empty body
}

tnbLib::sectPxLib::ExtrProfile_FivePoint::ExtrProfile_FivePoint
(
	const Standard_Integer theIndex,
	const word & theName
)
	: SectPx_ExtrProfile(theIndex, theName)
{
	// empty body
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::SetX0
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX0_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::SetX1
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX1_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::SetX2
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX2_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::SetX3
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX3_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::SetX4
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX4_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::SetValue0
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue0_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::SetValue1
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue1_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::SetValue2
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue2_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::SetValue3
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue3_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::SetValue4
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue4_, thePar, FunctionSIG);
}

tnbLib::word 
tnbLib::sectPxLib::ExtrProfile_FivePoint::RegObjTypeName() const
{
	return typeName_;
}

std::vector<Standard_Real> 
tnbLib::sectPxLib::ExtrProfile_FivePoint::X() const
{
	std::vector<Standard_Real> xs;
	xs.reserve(5);
	xs.push_back(X0().lock()->Value());
	xs.push_back(X1().lock()->Value());
	xs.push_back(X2().lock()->Value());
	xs.push_back(X3().lock()->Value());
	xs.push_back(X4().lock()->Value());
	return std::move(xs);
}

Standard_Real
tnbLib::sectPxLib::ExtrProfile_FivePoint::MinLower() const
{
	Debug_Null_Pointer(X0().lock());
	return X0().lock()->Value();
}

Standard_Real
tnbLib::sectPxLib::ExtrProfile_FivePoint::MaxUpper() const
{
	Debug_Null_Pointer((&theX0_)[NbPoints() - 1].lock());
	return (&theX0_)[NbPoints() - 1].lock()->Value();
}

Standard_Integer
tnbLib::sectPxLib::ExtrProfile_FivePoint::NbPoints() const
{
	return (Standard_Integer)nbPoints_;
}

tnbLib::Pnt2d
tnbLib::sectPxLib::ExtrProfile_FivePoint::Point
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
tnbLib::sectPxLib::ExtrProfile_FivePoint::NbChildren() const
{
	return Standard_Integer(12);
}

Standard_Boolean
tnbLib::sectPxLib::ExtrProfile_FivePoint::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean
tnbLib::sectPxLib::ExtrProfile_FivePoint::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	for (size_t i = 0; i < NbPoints(); i++)
	{
		ReturnTrueIfParBelongsToThisParent((&theX0_)[i], thePar);
		ReturnTrueIfParBelongsToThisParent((&theValue0_)[i], thePar);
	}

	ReturnTrueIfParBelongsToThisParent(Start(), thePar);
	ReturnTrueIfParBelongsToThisParent(End(), thePar);
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>>
tnbLib::sectPxLib::ExtrProfile_FivePoint::RetrieveChildren() const
{
	DefineChildList(children);
	for (size_t i = 0; i < NbPoints(); i++)
	{
		AddParToChildList((&theX0_)[i], children);
		AddParToChildList((&theValue0_)[i], children);
	}

	AddParToChildList(Start(), children);
	AddParToChildList(End(), children);
	return std::move(children);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::RemoveThisFromChildren() const
{
	for (size_t i = 0; i < NbPoints(); i++)
	{
		auto xPar = (&theX0_)[i].lock();
		if (xPar)
		{
			RemoveThisFromChild(xPar);
		}

		auto xValue = (&theValue0_)[i].lock();
		if (xValue)
		{
			RemoveThisFromChild(xValue);
		}
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

void tnbLib::sectPxLib::ExtrProfile_FivePoint::AddThisToChildren() const
{
	for (size_t i = 0; i < NbPoints(); i++)
	{
		AddThisParentToChildren((&theX0_)[i]);
		AddThisParentToChildren((&theValue0_)[i]);
	}

	AddThisParentToChildren(Start());
	AddThisParentToChildren(End());
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	AddThisParentToChild(thePar);
}