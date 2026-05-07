#include <HydStatic_HeelSpacing.hxx>

tnbLib::HydStatic_HeelSpacing::HydStatic_HeelSpacing
(
	const Standard_Integer theIndex,
	const word & theName
)
	: HydStatic_Entity(theIndex, theName)
{
	//- empty body
}

Standard_Boolean 
tnbLib::HydStatic_HeelSpacing::IsArbitrary() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::HydStatic_HeelSpacing::IsAsymmetric() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::HydStatic_HeelSpacing::IsStarboard() const
{
	return Standard_False;
}