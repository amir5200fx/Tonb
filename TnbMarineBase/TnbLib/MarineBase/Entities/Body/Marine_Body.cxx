#include <Marine_Body.hxx>

tnbLib::Marine_Body::Marine_Body()
{
}

tnbLib::Marine_Body::Marine_Body
(
	const Standard_Integer theIndex
)
	: Marine_Entity(theIndex)
{
}

tnbLib::Marine_Body::Marine_Body
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Marine_Entity(theIndex, theName)
{
}

Standard_Integer 
tnbLib::Marine_Body::NbSections() const
{
	return (Standard_Integer)theSections_.size();
}