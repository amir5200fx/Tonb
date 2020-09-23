#include <SectPx_CoordOverrider.hxx>

#include <SectPx_Coord.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::word 
tnbLib::SectPx_CoordOverrider::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::Pnt2d 
tnbLib::SectPx_CoordOverrider::CalcCoord() const
{
	Debug_Null_Pointer(Coord());
	auto pnt = Coord()->Coord();
	return std::move(pnt);
}