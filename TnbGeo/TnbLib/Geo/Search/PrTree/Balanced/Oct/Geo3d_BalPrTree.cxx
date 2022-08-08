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