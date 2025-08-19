#include <Geo3d_BalPrTree.hxx>

const Standard_Integer tnbLib::Geo3d_BalPrTreeBase::DEFAULT_UNBALANCING(2);

tnbLib::Geo3d_BalPrTreeOctant 
tnbLib::Geo3d_BalPrTreeBase::CalcOctant
(
	const Pnt3d & theCoord,
	const Pnt3d & theCentre
)
{
	if (theCoord.X() <= theCentre.X())
	{
		if (theCoord.Y() <= theCentre.Y())
		{
			if (theCoord.Z() <= theCentre.Z())
			{
				return Geo3d_BalPrTreeOctant::Bwd_SW;
			}
			else
			{
				return Geo3d_BalPrTreeOctant::Fwd_SW;
			}
		}
		else
		{
			if (theCoord.Z() <= theCentre.Z())
			{
				return Geo3d_BalPrTreeOctant::Bwd_NW;
			}
			else
			{
				return Geo3d_BalPrTreeOctant::Fwd_NW;
			}
		}
	}
	else
	{
		if (theCoord.Y() <= theCentre.Y())
		{
			if (theCoord.Z() <= theCentre.Z())
			{
				return Geo3d_BalPrTreeOctant::Bwd_SE;
			}
			else
			{
				return Geo3d_BalPrTreeOctant::Fwd_SE;
			}
		}
		else
		{
			if (theCoord.Z() <= theCentre.Z())
			{
				return Geo3d_BalPrTreeOctant::Bwd_NE;
			}
			else
			{
				return Geo3d_BalPrTreeOctant::Fwd_NE;
			}
		}
	}
}

Standard_Boolean 
tnbLib::Geo3d_BalPrTreeBase::IsBwdSW
(
	const Pnt3d & theCoord,
	const Pnt3d & theCentre
)
{
	if (theCoord.Z() <= theCentre.Z())
	{
		if (theCoord.Y() <= theCentre.Y())
		{
			if (theCoord.X() <= theCentre.X())
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}

Standard_Boolean
tnbLib::Geo3d_BalPrTreeBase::IsBwdSE
(
	const Pnt3d & theCoord,
	const Pnt3d & theCentre
)
{
	if (theCoord.Z() <= theCentre.Z())
	{
		if (theCoord.Y() <= theCentre.Y())
		{
			if (theCoord.X() >= theCentre.X())
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}

Standard_Boolean
tnbLib::Geo3d_BalPrTreeBase::IsBwdNW
(
	const Pnt3d & theCoord,
	const Pnt3d & theCentre
)
{
	if (theCoord.Z() <= theCentre.Z())
	{
		if (theCoord.Y() >= theCentre.Y())
		{
			if (theCoord.X() <= theCentre.X())
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}

Standard_Boolean
tnbLib::Geo3d_BalPrTreeBase::IsBwdNE
(
	const Pnt3d & theCoord,
	const Pnt3d & theCentre
)
{
	if (theCoord.Z() <= theCentre.Z())
	{
		if (theCoord.Y() >= theCentre.Y())
		{
			if (theCoord.X() >= theCentre.X())
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}

Standard_Boolean
tnbLib::Geo3d_BalPrTreeBase::IsFwdSW
(
	const Pnt3d & theCoord,
	const Pnt3d & theCentre
)
{
	if (theCoord.Z() >= theCentre.Z())
	{
		if (theCoord.Y() <= theCentre.Y())
		{
			if (theCoord.X() <= theCentre.X())
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}

Standard_Boolean
tnbLib::Geo3d_BalPrTreeBase::IsFwdSE
(
	const Pnt3d & theCoord,
	const Pnt3d & theCentre
)
{
	if (theCoord.Z() >= theCentre.Z())
	{
		if (theCoord.Y() <= theCentre.Y())
		{
			if (theCoord.X() >= theCentre.X())
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}

Standard_Boolean
tnbLib::Geo3d_BalPrTreeBase::IsFwdNW
(
	const Pnt3d & theCoord,
	const Pnt3d & theCentre
)
{
	if (theCoord.Z() >= theCentre.Z())
	{
		if (theCoord.Y() >= theCentre.Y())
		{
			if (theCoord.X() <= theCentre.X())
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}

Standard_Boolean
tnbLib::Geo3d_BalPrTreeBase::IsFwdNE
(
	const Pnt3d & theCoord,
	const Pnt3d & theCentre
)
{
	if (theCoord.Z() >= theCentre.Z())
	{
		if (theCoord.Y() >= theCentre.Y())
		{
			if (theCoord.X() >= theCentre.X())
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}