#include <Aft_MetricPrcsrIdentifier.hxx>

#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Surface.hxx>

tnbLib::Pnt3d
tnbLib::Aft_MetricPrcsrIdentifier<tnbLib::Aft2d_EdgeSurface>::CalcCoord3D(const Pnt2d& thePt) const
{
	Debug_Null_Pointer(Geometry());
	return Geometry()->Value(thePt.X(), thePt.Y());
}