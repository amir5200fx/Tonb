#include <SectPx_Pnt_Offset.hxx>

tnbLib::sectPxLib::Pnt_Offset::Pnt_Offset
(
	const Standard_Integer theIndex, 
	const Standard_Real x, 
	const Standard_Real y
)
	: SectPx_MasterPnt(theIndex)
	, theX_(x)
	, theY_(y)
{
	// empty body
}

tnbLib::sectPxLib::Pnt_Offset::Pnt_Offset
(
	const Standard_Integer theIndex,
	const word & theName,
	const Standard_Real x,
	const Standard_Real y
)
	: SectPx_MasterPnt(theIndex, theName)
	, theX_(x)
	, theY_(y)
{
	// empty body
}

const char* tnbLib::sectPxLib::Pnt_Offset::typeName_ = "pnt_offset";

tnbLib::word 
tnbLib::sectPxLib::Pnt_Offset::RegObjTypeName() const
{
	return typeName_;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_Offset::IsComplete() const
{
	return Standard_True;
}

typename tnbLib::sectPxLib::pntType 
tnbLib::sectPxLib::Pnt_Offset::PntType() const
{
	return sectPxLib::pntType::offset;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_Offset::IsOffset() const
{
	return Standard_True;
}

Standard_Integer 
tnbLib::sectPxLib::Pnt_Offset::NbChildren() const
{
	return 0;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_Offset::HasChildren() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_Offset::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>> 
tnbLib::sectPxLib::Pnt_Offset::RetrieveChildren() const
{
	return std::vector<std::shared_ptr<SectPx_Child>>();
}

void tnbLib::sectPxLib::Pnt_Offset::RemoveThisFromChildren() const
{
	// empty body
}

void tnbLib::sectPxLib::Pnt_Offset::AddThisToChildren() const
{
	// empty body
}

void tnbLib::sectPxLib::Pnt_Offset::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	// empty body
}

void tnbLib::sectPxLib::Pnt_Offset::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	// empty body
}