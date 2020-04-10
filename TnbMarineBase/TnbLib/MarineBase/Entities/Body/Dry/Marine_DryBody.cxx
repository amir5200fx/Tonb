#include <Marine_DryBody.hxx>

tnbLib::Marine_DryBody::Marine_DryBody()
{
}

tnbLib::Marine_DryBody::Marine_DryBody
(
	const Standard_Integer theIndex
)
	: Marine_HullBody(theIndex)
{
}

tnbLib::Marine_DryBody::Marine_DryBody
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_HullBody(theIndex, theName)
{
}