#include <Marine_TankBody.hxx>

tnbLib::Marine_TankBody::Marine_TankBody()
{
}

tnbLib::Marine_TankBody::Marine_TankBody
(
	const Standard_Integer theIndex
)
	: Marine_Body(theIndex)
{
}

tnbLib::Marine_TankBody::Marine_TankBody
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Marine_Body(theIndex, theName)
{
}