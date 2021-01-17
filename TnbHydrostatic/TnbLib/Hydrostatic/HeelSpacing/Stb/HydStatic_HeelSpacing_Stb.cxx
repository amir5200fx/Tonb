#include <HydStatic_HeelSpacing_Stb.hxx>

#include <HydStatic_Tools.hxx>
#include <math.h>

tnbLib::hydStcLib::HeelSpacing_Stb::HeelSpacing_Stb
(
	const Standard_Integer theIndex,
	const word & theName
)
	: HydStatic_HeelSpacing(theIndex, theName)
{
	// empty body
}

Standard_Boolean 
tnbLib::hydStcLib::HeelSpacing_Stb::IsStarboard() const
{
	return Standard_True;
}

void tnbLib::hydStcLib::HeelSpacing_Stb::Perform
(
	const Standard_Integer theNbHeels
)
{
	auto spacing = HydStatic_Tools::UniformSpacing(theNbHeels, 0, M_PI_2);
	SetSpacing(std::move(spacing));

	Change_IsDone() = Standard_True;
}

void tnbLib::hydStcLib::HeelSpacing_Stb::Perform
(
	const std::vector<Standard_Real>& theHeels
)
{
	auto spacing = HydStatic_Tools::CustomSpacing(theHeels, 0, M_PI_2);
	SetSpacing(std::move(spacing));

	Change_IsDone() = Standard_True;
}