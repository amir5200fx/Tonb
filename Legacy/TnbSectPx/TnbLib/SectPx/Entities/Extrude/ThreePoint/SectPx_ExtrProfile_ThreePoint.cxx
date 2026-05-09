#include <SectPx_ExtrProfile_ThreePoint.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::ExtrProfile_ThreePoint::typeName_("extrProfile_twoPoint");
const short tnbLib::sectPxLib::ExtrProfile_ThreePoint::nbPoints_ = 3;

tnbLib::sectPxLib::ExtrProfile_ThreePoint::ExtrProfile_ThreePoint
(
	const Standard_Integer theIndex
)
	: SectPx_ExtrProfile(theIndex)
{
	// empty body
}

tnbLib::sectPxLib::ExtrProfile_ThreePoint::ExtrProfile_ThreePoint
(
	const Standard_Integer theIndex,
	const word & theName
)
	: SectPx_ExtrProfile(theIndex, theName)
{
	// empty body
}

void tnbLib::sectPxLib::ExtrProfile_ThreePoint::SetX0
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX0_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_ThreePoint::SetX1
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX1_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_ThreePoint::SetX2
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX2_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_ThreePoint::SetValue0
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue0_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_ThreePoint::SetValue1
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue1_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_ThreePoint::SetValue2
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue2_, thePar, FunctionSIG);
}

std::shared_ptr<tnbLib::SectPx_Par>
tnbLib::sectPxLib::ExtrProfile_ThreePoint::Start() const
{
	return theX0_.lock();
}

std::shared_ptr<tnbLib::SectPx_Par>
tnbLib::sectPxLib::ExtrProfile_ThreePoint::End() const
{
	return theX2_.lock();
}

tnbLib::word 
tnbLib::sectPxLib::ExtrProfile_ThreePoint::RegObjTypeName() const
{
	return typeName_;
}

std::vector<Standard_Real> 
tnbLib::sectPxLib::ExtrProfile_ThreePoint::X() const
{
	std::vector<Standard_Real> xs;
	xs.reserve(3);
	xs.push_back(X0().lock()->Value());
	xs.push_back(X1().lock()->Value());
	xs.push_back(X2().lock()->Value());
	return std::move(xs);
}

Standard_Real
tnbLib::sectPxLib::ExtrProfile_ThreePoint::MinLower() const
{
	Debug_Null_Pointer(X0().lock());
	return X0().lock()->Value();
}

Standard_Real
tnbLib::sectPxLib::ExtrProfile_ThreePoint::MaxUpper() const
{
	Debug_Null_Pointer((&theX0_)[NbPoints() - 1].lock());
	return (&theX0_)[NbPoints() - 1].lock()->Value();
}

Standard_Integer
tnbLib::sectPxLib::ExtrProfile_ThreePoint::NbPoints() const
{
	return (Standard_Integer)nbPoints_;
}

tnbLib::Pnt2d
tnbLib::sectPxLib::ExtrProfile_ThreePoint::Point
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
tnbLib::sectPxLib::ExtrProfile_ThreePoint::NbChildren() const
{
	return Standard_Integer(8);
}

Standard_Boolean
tnbLib::sectPxLib::ExtrProfile_ThreePoint::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean
tnbLib::sectPxLib::ExtrProfile_ThreePoint::HasChild
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
tnbLib::sectPxLib::ExtrProfile_ThreePoint::RetrieveChildren() const
{
	DefineChildList(children);
	for (size_t i = 0; i < NbPoints(); i++)
	{
		AddParToChildList((&theX0_)[i], children);
		AddParToChildList((&theValue0_)[i], children);
	}

	return std::move(children);
}

void tnbLib::sectPxLib::ExtrProfile_ThreePoint::RemoveThisFromChildren() const
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

void tnbLib::sectPxLib::ExtrProfile_ThreePoint::AddThisToChildren() const
{
	for (size_t i = 0; i < NbPoints(); i++)
	{
		AddThisParentToChildren((&theX0_)[i]);
		AddThisParentToChildren((&theValue0_)[i]);
	}
}

void tnbLib::sectPxLib::ExtrProfile_ThreePoint::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}

void tnbLib::sectPxLib::ExtrProfile_ThreePoint::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	AddThisParentToChild(thePar);
}