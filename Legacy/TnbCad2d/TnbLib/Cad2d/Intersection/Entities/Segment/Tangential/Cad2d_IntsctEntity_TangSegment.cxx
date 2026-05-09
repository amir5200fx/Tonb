#include <Cad2d_IntsctEntity_TangSegment.hxx>

Standard_Real 
tnbLib::Cad2d_IntsctEntity_TangSegment::CharParameter() const
{
	return MEAN(Parameter0(), Parameter1());
}