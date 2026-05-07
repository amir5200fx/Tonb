#include <ISC08_SolutionData_Passenger.hxx>

#include <StbGMaker_Model.hxx>
#include <HydStatic_Shapes.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::isc08Lib::SolutionData_Passenger::IsUpdated
(
	const solutionOrder theSolution
) const
{
	return (int)theCurrent_ >= (int)theSolution;
}
