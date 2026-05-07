#include <ShapePx_Spacing.hxx>

#include <SectPx_Limits.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::ShapePx_Spacing::ShapePx_Spacing
(
	const std::shared_ptr<SectPx_Limits>& theLimits
)
	: theLimits_(theLimits)
{
	// empty body
}

tnbLib::ShapePx_Spacing::ShapePx_Spacing
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<SectPx_Limits>& theLimits
)
	: ShapePx_Entity(theIndex, theName)
	, theLimits_(theLimits)
{
	// empty body
}

Standard_Real 
tnbLib::ShapePx_Spacing::Lower() const
{
	Debug_Null_Pointer(Limits());
	return Limits()->Lower();
}

Standard_Real
tnbLib::ShapePx_Spacing::Upper() const
{
	Debug_Null_Pointer(Limits());
	return Limits()->Upper();
}