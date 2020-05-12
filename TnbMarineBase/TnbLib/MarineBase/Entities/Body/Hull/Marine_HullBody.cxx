#include <Marine_HullBody.hxx>

#include <Global_Macros.hxx>

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

Standard_Boolean 
tnbLib::Marine_HullBody::IsLaunched() const
{
	return IsWetted() OR IsDry();
}