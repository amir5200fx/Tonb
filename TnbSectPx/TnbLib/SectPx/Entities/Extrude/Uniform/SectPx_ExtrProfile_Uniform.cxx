#include <SectPx_ExtrProfile_Uniform.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::ExtrProfile_Uniform::typeName_("extrProfile_uniform");
const short tnbLib::sectPxLib::ExtrProfile_Uniform::nbPoints_ = 1;

tnbLib::sectPxLib::ExtrProfile_Uniform::ExtrProfile_Uniform
(
	const Standard_Integer theIndex
)
	: SectPx_ExtrProfile(theIndex)
{
	// empty body
}

tnbLib::sectPxLib::ExtrProfile_Uniform::ExtrProfile_Uniform
(
	const Standard_Integer theIndex,
	const word & theName
)
	: SectPx_ExtrProfile(theIndex, theName)
{
	// empty body
}

void tnbLib::sectPxLib::ExtrProfile_Uniform::SetX0
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX0_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_Uniform::SetX1
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theX1_, thePar, FunctionSIG);
}

void tnbLib::sectPxLib::ExtrProfile_Uniform::SetValue
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theValue_, thePar, FunctionSIG);
}

std::vector<Standard_Real> 
tnbLib::sectPxLib::ExtrProfile_Uniform::X() const
{
	std::vector<Standard_Real> xs;
	xs.reserve(2);
	xs.push_back(Lower());
	xs.push_back(Upper());
	return std::move(xs);
}

Standard_Real 
tnbLib::sectPxLib::ExtrProfile_Uniform::MinLower() const
{
	Debug_Null_Pointer(X0().lock());
	return X0().lock()->Value();
}

Standard_Real 
tnbLib::sectPxLib::ExtrProfile_Uniform::MaxUpper() const
{
	Debug_Null_Pointer(X1().lock());
	return X1().lock()->Value();
}

Standard_Integer 
tnbLib::sectPxLib::ExtrProfile_Uniform::NbPoints() const
{
	return (Standard_Integer)nbPoints_;
}

tnbLib::Pnt2d 
tnbLib::sectPxLib::ExtrProfile_Uniform::Point
(
	const Standard_Integer /*theIndex*/
) const
{
	Debug_Null_Pointer(X0().lock());
	Debug_Null_Pointer(Value().lock());
	Pnt2d pt(X0().lock()->Value(), Value().lock()->Value());
	return std::move(pt);
}

Standard_Integer 
tnbLib::sectPxLib::ExtrProfile_Uniform::NbChildren() const
{
	return Standard_Integer(5);
}

Standard_Boolean 
tnbLib::sectPxLib::ExtrProfile_Uniform::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::ExtrProfile_Uniform::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(X0(), thePar);
	ReturnTrueIfParBelongsToThisParent(X1(), thePar);
	ReturnTrueIfParBelongsToThisParent(Value(), thePar);

	ReturnTrueIfParBelongsToThisParent(Start(), thePar);
	ReturnTrueIfParBelongsToThisParent(End(), thePar);
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>> 
tnbLib::sectPxLib::ExtrProfile_Uniform::RetrieveChildren() const
{
	DefineChildList(children);
	AddParToChildList(X0(), children);
	AddParToChildList(X1(), children);
	AddParToChildList(Value(), children);

	AddParToChildList(Start(), children);
	AddParToChildList(End(), children);
	return std::move(children);
}

void tnbLib::sectPxLib::ExtrProfile_Uniform::RemoveThisFromChildren() const
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

	auto vPar = Value().lock();
	if (vPar)
	{
		RemoveThisFromChild(vPar);
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

void tnbLib::sectPxLib::ExtrProfile_Uniform::AddThisToChildren() const
{
	AddThisParentToChildren(X0());
	AddThisParentToChildren(X1());
	AddThisParentToChildren(Value());

	AddThisParentToChildren(Start());
	AddThisParentToChildren(End());
}

void tnbLib::sectPxLib::ExtrProfile_Uniform::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}

void tnbLib::sectPxLib::ExtrProfile_Uniform::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	AddThisParentToChild(thePar);
}