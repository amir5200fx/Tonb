#include <Marine_GraphAxis.hxx>

tnbLib::Marine_GraphAxis::Marine_GraphAxis()
{
}

tnbLib::Marine_GraphAxis::Marine_GraphAxis
(
	const Standard_Integer theIndex
)
	: Marine_GraphEntity(theIndex)
{
}

tnbLib::Marine_GraphAxis::Marine_GraphAxis
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_GraphEntity(theIndex, theName)
{
}

