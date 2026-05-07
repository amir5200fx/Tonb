#include <HydStatic_CrsCurveQ.hxx>

Standard_Real 
tnbLib::HydStatic_CrsCurveQ::FirstLeverArm() const
{
	return FirstValue();
}

Standard_Real 
tnbLib::HydStatic_CrsCurveQ::LastLeverArm() const
{
	return LastValue();
}

Standard_Real 
tnbLib::HydStatic_CrsCurveQ::LowerDispv() const
{
	return Lower();
}

Standard_Real 
tnbLib::HydStatic_CrsCurveQ::UpperDispv() const
{
	return Upper();
}

Standard_Real 
tnbLib::HydStatic_CrsCurveQ::LeverArm(const Standard_Real theVolume) const
{
	return Value(theVolume);
}