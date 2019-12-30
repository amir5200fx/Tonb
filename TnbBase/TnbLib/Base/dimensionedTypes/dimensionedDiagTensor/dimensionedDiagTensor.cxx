#include <dimensionedDiagTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


	// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

	dimensionedScalar tr(const dimensionedDiagTensor& ddt)
	{
		return dimensionedScalar
		(
			"tr(" + ddt.name() + ')',
			ddt.dimensions(),
			tr(ddt.value())
		);
	}


	dimensionedScalar det(const dimensionedDiagTensor& ddt)
	{
		return dimensionedScalar
		(
			"det(" + ddt.name() + ')',
			pow(ddt.dimensions(), tensor::dim),
			det(ddt.value())
		);
	}


	dimensionedDiagTensor inv(const dimensionedDiagTensor& ddt)
	{
		return dimensionedDiagTensor
		(
			"inv(" + ddt.name() + ')',
			dimless / ddt.dimensions(),
			inv(ddt.value())
		);
	}


	dimensionedDiagTensor diag(const dimensionedTensor& dt)
	{
		return dimensionedDiagTensor
		(
			"diag(" + dt.name() + ')',
			dt.dimensions(),
			diag(dt.value())
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //