#include <SectPx_nonParFieldFun.hxx>

Standard_Boolean 
tnbLib::SectPx_nonParFieldFun::IsComplete() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_nonParFieldFun::HasChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	return Standard_False;
}

void tnbLib::SectPx_nonParFieldFun::RemoveThisFromChilds() const
{
	//- Empty body
}

void tnbLib::SectPx_nonParFieldFun::AddThisToChilds() const
{
	//- Empty body
}

void tnbLib::SectPx_nonParFieldFun::AddThisToChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	//- Empty body
}

void tnbLib::SectPx_nonParFieldFun::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	//- Empty body
}