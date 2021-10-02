#include <HydStatic_CrsCurveQ.hxx>

Standard_Real 
tnbLib::HydStatic_CrsCurveQ::LeverArm0() const
{
	return FirstValue();
}

Standard_Real 
tnbLib::HydStatic_CrsCurveQ::LeverArm1() const
{
	return LastValue();
}

Standard_Real 
tnbLib::HydStatic_CrsCurveQ::Dispv0() const
{
	return Lower();
}

Standard_Real 
tnbLib::HydStatic_CrsCurveQ::Dispv1() const
{
	return Upper();
}

Standard_Real 
tnbLib::HydStatic_CrsCurveQ::LeverArm(const Standard_Real theVolume) const
{
	return Value(theVolume);
}