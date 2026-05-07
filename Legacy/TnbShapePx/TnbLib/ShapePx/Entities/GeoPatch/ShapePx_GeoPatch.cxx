#include <ShapePx_GeoPatch.hxx>

tnbLib::ShapePx_GeoPatch::ShapePx_GeoPatch
(
	const Standard_Integer theIndex,
	const word & theName
)
	: ShapePx_Entity(theIndex, theName)
{
	//- empty body
}

tnbLib::ShapePx_GeoPatch::ShapePx_GeoPatch
(
	const Handle(Geom_Surface) theSurface
)
	: theGeometry_(theSurface)
{
	//- empty body
}

tnbLib::ShapePx_GeoPatch::ShapePx_GeoPatch
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom_Surface) theSurface
)
	: ShapePx_Entity(theIndex, theName)
	, theGeometry_(theSurface)
{
	//- empty body
}