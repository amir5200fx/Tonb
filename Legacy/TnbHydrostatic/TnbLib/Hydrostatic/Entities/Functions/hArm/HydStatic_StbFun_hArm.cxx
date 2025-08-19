#include <HydStatic_StbFun_hArm.hxx>

#include <HydStatic_hArmCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::hydStcLib::StbFun_hArm::MinHeel() const
{
	Debug_Null_Pointer(Arm());
	return Arm()->MinHeel();
}

Standard_Real 
tnbLib::hydStcLib::StbFun_hArm::MaxHeel() const
{
	Debug_Null_Pointer(Arm());
	return Arm()->MaxHeel();
}

Standard_Real 
tnbLib::hydStcLib::StbFun_hArm::Value
(
	const Standard_Real thePhi
) const
{
	Debug_Null_Pointer(Arm());
	return Arm()->Value(thePhi);
}