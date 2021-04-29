#include <Mesh_ReferenceValues.hxx>

tnbLib::Mesh_ReferenceValues::Mesh_ReferenceValues
(
	const Standard_Real theBaseSize
)
	: theBase_(theBaseSize)
{
	theBoundaryGrowthRate_ = Mesh_VariationRateInfo::moderate;
	theDefaultGrowthRate_ = Mesh_VariationRateInfo::moderate;
}