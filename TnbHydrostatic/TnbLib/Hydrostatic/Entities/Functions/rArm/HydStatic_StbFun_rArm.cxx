#include <HydStatic_StbFun_rArm.hxx>

#include <HydStatic_rArmCurve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Real
tnbLib::hydStcLib::StbFun_rArm::MinHeel() const
{
	Debug_Null_Pointer(Arm());
	return Arm()->MinHeel();
}

Standard_Real
tnbLib::hydStcLib::StbFun_rArm::MaxHeel() const
{
	Debug_Null_Pointer(Arm());
	return Arm()->MaxHeel();
}

Standard_Real
tnbLib::hydStcLib::StbFun_rArm::Value
(
	const Standard_Real thePhi
) const
{
	Debug_Null_Pointer(Arm());
	return Arm()->Value(thePhi);
}