#include <HydStatic_SolutionData_Coeffs.hxx>

const std::string tnbLib::hydStcLib::SolutionData_Coeffs::extension = ".hssoldcoeffs";

Standard_Boolean 
tnbLib::hydStcLib::SolutionData_Coeffs::IsUpdated
(
	const solutionOrder theSolution
) const
{
	return (int)theCurrent_ >= (int)theSolution;
}