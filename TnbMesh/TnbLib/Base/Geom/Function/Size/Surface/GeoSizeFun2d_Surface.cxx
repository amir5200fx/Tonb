#include <GeoSizeFun2d_Surface.hxx>

#include <Geo2d_SizeFunction.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom_Surface.hxx>

Standard_Real
tnbLib::GeoSizeFun2d_Surface::Value
(
	const Pnt2d & theCoord
) const
{
	Debug_Null_Pointer(Surface());
	Debug_Null_Pointer(SizeFun3d());

	auto pt = Surface()->Value(theCoord.X(), theCoord.Y());
	return SizeFun3d()->Value(pt);
}