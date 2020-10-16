#include <SectPx_Parent.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::SectPx_Parent::NbChildren() const
{
	return 0;
}

Standard_Integer 
tnbLib::SectPx_Parent::NbChildMaps() const
{
	return 0;
}

Standard_Boolean 
tnbLib::SectPx_Parent::IsPnt() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Parent::IsDatum() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Parent::IsGeoMap() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Parent::IsFieldFun() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Parent::IsController() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Parent::IsCPtsMap() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Parent::IsCloud() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Parent::IsParent() const
{
	return Standard_True;
}

Standard_Boolean
tnbLib::SectPx_Parent::HasChildren() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Parent::HasChildMap() const
{
	return Standard_False;
}

std::shared_ptr<tnbLib::SectPx_Parent> 
tnbLib::SectPx_Parent::ChildMap
(
	const Standard_Integer theIndex
) const
{
	Debug_If_Condition_Message(NOT HasChildren(),"not supposed to be called by parents that have no children");
	return nullptr;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>> 
tnbLib::SectPx_Parent::RetrieveChildren() const
{
	Debug_If_Condition_Message(HasChildMap(), "there is no child for this type of the parent");
	return std::vector<std::shared_ptr<SectPx_Child>>();
}

void tnbLib::SectPx_Parent::Print(Ostream & out) const
{
	//- empty body
}