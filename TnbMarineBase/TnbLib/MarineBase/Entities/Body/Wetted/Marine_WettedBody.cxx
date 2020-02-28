#include <Marine_WettedBody.hxx>

tnbLib::Marine_WettedBody::Marine_WettedBody()
{
}

tnbLib::Marine_WettedBody::Marine_WettedBody
(
	const Standard_Integer theIndex
)
	: Marine_Body(theIndex)
{
}

tnbLib::Marine_WettedBody::Marine_WettedBody
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Marine_Body(theIndex, theName)
{
}