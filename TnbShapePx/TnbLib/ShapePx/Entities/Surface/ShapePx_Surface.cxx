#include <ShapePx_Surface.hxx>

tnbLib::ShapePx_Surface::ShapePx_Surface
(
	const Standard_Integer theIndex,
	const word & theName
)
	: ShapePx_Entity(theIndex, theName)
{
	// empty body
}

tnbLib::ShapePx_Surface::ShapePx_Surface
(
	const std::shared_ptr<ShapePx_Patch>& thePatch,
	const std::shared_ptr<SectPx_CurveQ>& theCurve,
	const std::shared_ptr<ShapePx_Spacing>& theSpace
)
	: thePatch_(thePatch)
	, theCurve_(theCurve)
	, theSpace_(theSpace)
{
	// empty body
}

tnbLib::ShapePx_Surface::ShapePx_Surface
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<ShapePx_Patch>& thePatch,
	const std::shared_ptr<SectPx_CurveQ>& theCurve, 
	const std::shared_ptr<ShapePx_Spacing>& theSpace
)
	: ShapePx_Entity(theIndex, theName)
	, thePatch_(thePatch)
	, theCurve_(theCurve)
	, theSpace_(theSpace)
{
	// empty body
}