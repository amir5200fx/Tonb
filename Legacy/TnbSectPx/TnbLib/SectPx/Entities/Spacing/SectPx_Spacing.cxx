#include <SectPx_Spacing.hxx>
#include <SectPx_Limits.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::SectPx_Spacing::SectPx_Spacing
(
	const std::shared_ptr<SectPx_Limits>& theLimits
)
	: theLimits_(theLimits)
{
	// empty body
}

tnbLib::SectPx_Spacing::SectPx_Spacing
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<SectPx_Limits>& theLimits
)
	: SectPx_Parent(theIndex, theName)
	, theLimits_(theLimits)
{
	// empty body
}

Standard_Real
tnbLib::SectPx_Spacing::Lower() const
{
	Debug_Null_Pointer(Limits());
	return Limits()->Lower();
}

Standard_Real
tnbLib::SectPx_Spacing::Upper() const
{
	Debug_Null_Pointer(Limits());
	return Limits()->Upper();
}

Standard_Boolean 
tnbLib::SectPx_Spacing::IsShapeRegObj() const
{
	return Standard_True;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Spacing::RegObjType() const
{
	return sectPxLib::regObjType::spacing;
}

Standard_Integer 
tnbLib::SectPx_Spacing::NbChildren() const
{
	return 0;
}

Standard_Boolean 
tnbLib::SectPx_Spacing::HasChildren() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Spacing::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	return Standard_False;
}

void tnbLib::SectPx_Spacing::RemoveThisFromChildren() const
{
	//- empty body
}

void tnbLib::SectPx_Spacing::AddThisToChildren() const
{
	//- empty body
}

void tnbLib::SectPx_Spacing::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& /*thePar*/
) const
{
	//- empty body
}

void tnbLib::SectPx_Spacing::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& /*thePar*/
) const
{
	//- empty body
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>>
tnbLib::SectPx_Spacing::RetrieveChildren() const
{
	return std::vector<std::shared_ptr<SectPx_Child>>();
}