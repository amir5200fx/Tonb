#include <Geo2d_BalPrTree.hxx>

const Standard_Integer tnbLib::Geo2d_BalPrTreeBase::DEFAULT_UNBALANCING(2);

tnbLib::Geo2d_BalPrTreeQuad 
tnbLib::Geo2d_BalPrTreeBase::CalcQuadrant
(
	const Pnt2d & theCoord, 
	const Pnt2d & theCentre
)
{
	if (theCoord.X() <= theCentre.X())
		if (theCoord.Y() <= theCentre.Y())
			return Geo2d_BalPrTreeQuad::SW;
		else
			return Geo2d_BalPrTreeQuad::NW;
	else
	{
		if (theCoord.Y() <= theCentre.Y())
			return Geo2d_BalPrTreeQuad::SE;
		else
			return Geo2d_BalPrTreeQuad::NE;
	}
}

Standard_Boolean 
tnbLib::Geo2d_BalPrTreeBase::IsSW
(
	const Pnt2d & theCoord,
	const Pnt2d & theCentre
)
{
	if (theCoord.Y() <= theCentre.Y())
	{
		if (theCoord.X() <= theCentre.X())
		{
			return Standard_True;
		}
	}
	return Standard_False;
}

Standard_Boolean 
tnbLib::Geo2d_BalPrTreeBase::IsSE
(
	const Pnt2d & theCoord, 
	const Pnt2d & theCentre
)
{
	if (theCoord.Y() <= theCentre.Y())
	{
		if (theCoord.X() >= theCentre.X())
		{
			return Standard_True;
		}
	}
	return Standard_False;
}

Standard_Boolean 
tnbLib::Geo2d_BalPrTreeBase::IsNE
(
	const Pnt2d & theCoord,
	const Pnt2d & theCentre
)
{
	if (theCoord.Y() >= theCentre.Y())
	{
		if (theCoord.X() >= theCentre.X())
		{
			return Standard_True;
		}
	}
	return Standard_False;
}

Standard_Boolean 
tnbLib::Geo2d_BalPrTreeBase::IsNW
(
	const Pnt2d & theCoord,
	const Pnt2d & theCentre
)
{
	if (theCoord.Y() >= theCentre.Y())
	{
		if (theCoord.X() <= theCentre.X())
		{
			return Standard_True;
		}
	}
	return Standard_False;
}
