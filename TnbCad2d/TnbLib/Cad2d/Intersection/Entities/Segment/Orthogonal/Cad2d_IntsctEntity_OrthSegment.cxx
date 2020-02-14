#include <Cad2d_IntsctEntity_OrthSegment.hxx>

tnbLib::Cad2d_IntsctEntity_OrthSegment::Cad2d_IntsctEntity_OrthSegment()
{
}

tnbLib::Cad2d_IntsctEntity_OrthSegment::Cad2d_IntsctEntity_OrthSegment
(
	const Standard_Integer theIndex
)
	: Cad2d_IntsctEntity_Segment(theIndex)
{
}

tnbLib::Cad2d_IntsctEntity_OrthSegment::Cad2d_IntsctEntity_OrthSegment
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Cad2d_IntsctEntity_Segment(theIndex, theName)
{
}