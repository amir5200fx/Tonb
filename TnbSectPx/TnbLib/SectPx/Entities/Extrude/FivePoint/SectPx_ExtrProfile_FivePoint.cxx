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


Standard_Real
tnbLib::sectPxLib::ExtrProfile_FivePoint::Lower() const
{
	Debug_Null_Pointer(X0().lock());
	return X0().lock()->Value();
}

Standard_Real
tnbLib::sectPxLib::ExtrProfile_FivePoint::Upper() const
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
	return Standard_Integer(3);
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
}

void tnbLib::sectPxLib::ExtrProfile_FivePoint::AddThisToChildren() const
{
	for (size_t i = 0; i < NbPoints(); i++)
	{
		AddThisParentToChildren((&theX0_)[i]);
		AddThisParentToChildren((&theValue0_)[i]);
	}
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