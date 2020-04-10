#include <Marine_HullBody.hxx>

tnbLib::Marine_HullBody::Marine_HullBody()
{
}

tnbLib::Marine_HullBody::Marine_HullBody
(
	const Standard_Integer theIndex
)
	: Marine_Body(theIndex)
{
}

tnbLib::Marine_HullBody::Marine_HullBody
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Marine_Body(theIndex, theName)
{
}