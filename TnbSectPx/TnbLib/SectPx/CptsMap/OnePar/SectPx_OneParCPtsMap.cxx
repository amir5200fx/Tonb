#include <SectPx_OneParCPtsMap.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_ParTools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Boolean
tnbLib::SectPx_OneParCPtsMap::IsSingle() const
{
	return Standard_False;
}

Standard_Boolean
tnbLib::SectPx_OneParCPtsMap::IsDistribution() const
{
	return Standard_False;
}

Standard_Boolean
tnbLib::SectPx_OneParCPtsMap::IsOnePar() const
{
	return Standard_True;
}

void tnbLib::SectPx_OneParCPtsMap::SetPar
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent
	(
		thePar_, thePar,
		"void SetPar(const std::shared_ptr<SectPx_Phi>& thePar)"
	);
}

Standard_Integer
tnbLib::SectPx_OneParCPtsMap::NbChildren() const
{
	return 1;
}

Standard_Boolean
tnbLib::SectPx_OneParCPtsMap::IsComplete() const
{
	return (Standard_Boolean)Par().lock();
}

Standard_Boolean
tnbLib::SectPx_OneParCPtsMap::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean
tnbLib::SectPx_OneParCPtsMap::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(Par(), thePar);
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>>
tnbLib::SectPx_OneParCPtsMap::RetrieveChildren() const
{
	DefineChildList(children);
	AddParToChildList(Par(), children);
	return std::move(children);
}

void tnbLib::SectPx_OneParCPtsMap::RemoveThisFromChildren() const
{
	auto par = Par().lock();
	if (par)
	{
		RemoveThisFromChild(par);
	}
}

void tnbLib::SectPx_OneParCPtsMap::AddThisToChildren() const
{
	AddThisParentToChildren(Par());
}

void tnbLib::SectPx_OneParCPtsMap::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	AddThisParentToChild(thePar);
}

void tnbLib::SectPx_OneParCPtsMap::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}