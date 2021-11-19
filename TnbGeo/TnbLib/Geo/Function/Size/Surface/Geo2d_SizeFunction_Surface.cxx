#include <Geo2d_SizeFunction_Surface.hxx>

#include <Geo3d_SizeFunction.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Surface.hxx>

const std::string tnbLib::Geo2d_SizeFunction_Surface::extension = ".gfun2d";

Standard_Real
tnbLib::Geo2d_SizeFunction_Surface::Value
(
	const Pnt2d & theCoord
) const
{
	Debug_Null_Pointer(Surface());
	Debug_Null_Pointer(Size3d());

	auto pt = Surface()->Value(theCoord.X(), theCoord.Y());
	return Size3d()->Value(pt);
}