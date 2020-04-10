#include <Marine_BaseLine.hxx>

#include <Global_Macros.hxx>

namespace tnbLib
{
	const gp_Ax1 Marine_BaseLine::null(gp::OX());
}

tnbLib::Marine_BaseLine::Marine_BaseLine()
	: theBaseLib_(null)
{
}

tnbLib::Marine_BaseLine::Marine_BaseLine
(
	const gp_Ax2 & theSystem
)
	: theBaseLib_(theSystem.Location(), theSystem.XDirection())
{
}

Standard_Boolean 
tnbLib::Marine_BaseLine::IsNull() const
{
	return &BaseLine() IS_EQUAL &null;
}