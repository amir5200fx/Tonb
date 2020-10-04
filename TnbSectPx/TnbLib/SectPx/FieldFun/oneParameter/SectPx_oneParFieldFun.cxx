#include <SectPx_oneParFieldFun.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::SectPx_oneParFieldFun::NbChildren() const
{
	return 1;
}

Standard_Boolean 
tnbLib::SectPx_oneParFieldFun::IsComplete() const
{
	return (Standard_Boolean)Par().lock();
}

Standard_Boolean 
tnbLib::SectPx_oneParFieldFun::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean
tnbLib::SectPx_oneParFieldFun::HasChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(Par(), thePar);
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>>
tnbLib::SectPx_oneParFieldFun::RetrieveChildren() const
{
	DefineChildList(childs);
	AddParToChildList(Par(), childs);
	return std::move(childs);
}

void tnbLib::SectPx_oneParFieldFun::RemoveThisFromChildren() const
{
	auto par = Par().lock();
	if (par)
	{
		RemoveThisFromChild(par);
	}
}

void tnbLib::SectPx_oneParFieldFun::AddThisToChildren() const
{
	AddThisParentToAllChilds(Par());
}

void tnbLib::SectPx_oneParFieldFun::AddThisToChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	AddThisParentToChild(thePar);
}

void tnbLib::SectPx_oneParFieldFun::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}

void tnbLib::SectPx_oneParFieldFun::SetPar
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent
	(
		thePar_, thePar, 
		"void SetPhi(const std::shared_ptr<SectPx_Par>& thePar)"
	);
}