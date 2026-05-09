#include <Airfoil_NacaThickness_Profile.hxx>

#include <Airfoil_OffsetProfile.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::Airfoil_NacaThickness_Profile::CalcYt(const Standard_Real xPerc) const
{
	Debug_Null_Pointer(Profile());
	return Profile()->Value(xPerc);
}