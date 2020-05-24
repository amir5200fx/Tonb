#include <physicalConstants.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

// Avogadro constant (number of molecules in a mole)
const tnbLib::dimensionedScalar tnbLib::physicalConstant::A
(
	"A",
	dimensionSet(0, 0, 0, 0, -1, 0, 0),
	6.0221415e23
);


// Faraday's constant (charge of electron)
const tnbLib::dimensionedScalar tnbLib::physicalConstant::F
(
	"F",
	dimensionSet(0, 0, 1, 0, 0, 1, 0),
	9.6485309e4
);


// ************************************************************************* //