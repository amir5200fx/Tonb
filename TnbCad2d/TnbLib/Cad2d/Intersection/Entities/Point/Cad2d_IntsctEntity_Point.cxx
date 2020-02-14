#include <Cad2d_IntsctEntity_Point.hxx>

tnbLib::Cad2d_IntsctEntity_Point::Cad2d_IntsctEntity_Point()
{
}

tnbLib::Cad2d_IntsctEntity_Point::Cad2d_IntsctEntity_Point
(
	const Standard_Integer theIndex
)
	: Cad2d_IntsctEntity(theIndex)
{
}

tnbLib::Cad2d_IntsctEntity_Point::Cad2d_IntsctEntity_Point
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Cad2d_IntsctEntity(theIndex, theName)
{
}