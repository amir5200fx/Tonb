#include <Marine_Section.hxx>

#include <error.hxx>
#include <OSstream.hxx>

tnbLib::Marine_Section::Marine_Section
(
	const outer & theOuter, 
	const inner & theInner
)
	: theOuter_(theOuter)
	, theInner_(theInner)
{
}

tnbLib::Marine_Section::Marine_Section
(
	const Standard_Integer theIndex,
	const outer & theOuter,
	const inner & theInner
)
	: Marine_Entity(theIndex)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
}

tnbLib::Marine_Section::Marine_Section
(
	const Standard_Integer theIndex, 
	const word & theName,
	const outer & theOuter, 
	const inner & theInner
)
	: Marine_Entity(theIndex, theName)
	, theOuter_(theOuter)
	, theInner_(theInner)
{
}

Standard_Boolean 
tnbLib::Marine_Section::HasHole() const
{
	return (Standard_Boolean)theInner_;
}

Standard_Integer
tnbLib::Marine_Section::NbHoles() const
{
	if (HasHole())
	{
		(Standard_Integer)theInner_->size();
	}
	return 0;
}

Standard_Real 
tnbLib::Marine_Section::GetXcoord
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	Debug_Null_Pointer(theSection);
	return theSection->CoordinateSystem().Location().X();
}