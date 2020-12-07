#include <SectPx_ExtrProfile.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::SectPx_ExtrProfile::SetStart
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theStart_, thePar, FunctionSIG);
}

void tnbLib::SectPx_ExtrProfile::SetEnd
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent(theEnd_, thePar, FunctionSIG);
}

Standard_Real 
tnbLib::SectPx_ExtrProfile::Lower() const
{
	Debug_Null_Pointer(Start().lock());
	return Start().lock()->Value();
}

Standard_Real 
tnbLib::SectPx_ExtrProfile::Upper() const
{
	Debug_Null_Pointer(End().lock());
	return End().lock()->Value();
}

Standard_Boolean 
tnbLib::SectPx_ExtrProfile::IsExtrProfile() const
{
	return Standard_True;
}