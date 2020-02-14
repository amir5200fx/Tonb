#include <Cad2d_IntsctEntity_Segment.hxx>

tnbLib::Cad2d_IntsctEntity_Segment::Cad2d_IntsctEntity_Segment
(
	const Standard_Integer theIndex
)
	: Cad2d_IntsctEntity(theIndex)
{
}

tnbLib::Cad2d_IntsctEntity_Segment::Cad2d_IntsctEntity_Segment
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Cad2d_IntsctEntity(theIndex, theName)
{
}