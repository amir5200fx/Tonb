#include <Marine_SailBody.hxx>

tnbLib::Marine_SailBody::Marine_SailBody()
{
}

tnbLib::Marine_SailBody::Marine_SailBody
(
	const Standard_Integer theIndex
)
	: Marine_Body(theIndex)
{
}

tnbLib::Marine_SailBody::Marine_SailBody
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_Body(theIndex, theName)
{
}