#include <SectPx_Shape.hxx>

const char* tnbLib::SectPx_Shape::typeName_ = "shape";

tnbLib::word 
tnbLib::SectPx_Shape::RegObjTypeName() const
{
	return typeName_;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Shape::RegObjType() const
{
	return sectPxLib::regObjType::shape;
}

Standard_Boolean 
tnbLib::SectPx_Shape::IsSection() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Shape::IsProfile() const
{
	return Standard_False;
}