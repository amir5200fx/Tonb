#include <Marine_WettedBody.hxx>

tnbLib::Marine_WettedBody::Marine_WettedBody()
{
}

tnbLib::Marine_WettedBody::Marine_WettedBody
(
	const Standard_Integer theIndex
)
	: Marine_HullBody(theIndex)
{
}

tnbLib::Marine_WettedBody::Marine_WettedBody
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Marine_HullBody(theIndex, theName)
{
}