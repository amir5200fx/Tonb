#include <Marine_CGCompt.hxx>

tnbLib::Marine_CGCompt::Marine_CGCompt
(
	const Standard_Real theValue
)
	: theValue_(theValue)
{
}

tnbLib::Marine_CGCompt::Marine_CGCompt
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Standard_Real theValue
)
	: Marine_Entity(theIndex, theName)
	, theValue_(theValue)
{
}