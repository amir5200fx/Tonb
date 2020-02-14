#include <Cad2d_IntsctEntity_TangSegment.hxx>

tnbLib::Cad2d_IntsctEntity_TangSegment::Cad2d_IntsctEntity_TangSegment()
{
}

tnbLib::Cad2d_IntsctEntity_TangSegment::Cad2d_IntsctEntity_TangSegment
(
	const Standard_Integer theIndex
)
	: Cad2d_IntsctEntity_Segment(theIndex)
{
}

tnbLib::Cad2d_IntsctEntity_TangSegment::Cad2d_IntsctEntity_TangSegment
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Cad2d_IntsctEntity_Segment(theIndex, theName)
{
}

Standard_Real 
tnbLib::Cad2d_IntsctEntity_TangSegment::CharParameter() const
{
	return MEAN(Parameter0(), Parameter1());
}