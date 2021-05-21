#include <HydStatic_SolutionData_Coeffs.hxx>

Standard_Boolean 
tnbLib::hydStcLib::SolutionData_Coeffs::IsUpdated
(
	const solutionOrder theSolution
) const
{
	return (int)theCurrent_ >= (int)theSolution;
}