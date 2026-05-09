#include <HydStatic_HeelSpacing_Asym.hxx>

#include <HydStatic_Tools.hxx>
#include <math.h>

tnbLib::hydStcLib::HeelSpacing_Asym::HeelSpacing_Asym
(
	const Standard_Integer theIndex,
	const word & theName
)
	: HydStatic_HeelSpacing(theIndex, theName)
{
	// empty body
}

Standard_Boolean 
tnbLib::hydStcLib::HeelSpacing_Asym::IsAsymmetric() const
{
	return Standard_True;
}

void tnbLib::hydStcLib::HeelSpacing_Asym::Perform
(
	const Standard_Integer theNbHeels
)
{
	auto spacing = HydStatic_Tools::UniformSpacing(theNbHeels, -M_PI_2, M_PI_2);
	SetSpacing(std::move(spacing));

	Change_IsDone() = Standard_True;
}

void tnbLib::hydStcLib::HeelSpacing_Asym::Perform
(
	const std::vector<Standard_Real>& theHeels
)
{
	auto spacing = HydStatic_Tools::CustomSpacing(theHeels, -M_PI_2, M_PI_2);
	SetSpacing(std::move(spacing));

	Change_IsDone() = Standard_True;
}
