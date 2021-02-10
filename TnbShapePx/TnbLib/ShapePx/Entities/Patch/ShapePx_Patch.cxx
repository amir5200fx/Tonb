#include <ShapePx_Patch.hxx>

tnbLib::ShapePx_Patch::ShapePx_Patch
(
	const Standard_Integer theIndex
)
	: ShapePx_Entity(theIndex)
{
	// empty body
}

tnbLib::ShapePx_Patch::ShapePx_Patch
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: ShapePx_Entity(theIndex, theName)
{
	// empty body
}

tnbLib::ShapePx_Patch::ShapePx_Patch
(
	const std::shared_ptr<SectPx_Registry>& theRegistry,
	const std::shared_ptr<ShapePx_Section>& theSection
)
	: theSection_(theSection)
	, theRegistry_(theRegistry)
{
	// empty body
}

tnbLib::ShapePx_Patch::ShapePx_Patch
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<SectPx_Registry>& theRegistry,
	const std::shared_ptr<ShapePx_Section>& theSection
)
	: ShapePx_Entity(theIndex, theName)
	, theSection_(theSection)
	, theRegistry_(theRegistry)
{
	// empty body
}

Standard_Boolean 
tnbLib::ShapePx_Patch::IsExtruded() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::ShapePx_Patch::IsRevolved() const
{
	return Standard_False;
}