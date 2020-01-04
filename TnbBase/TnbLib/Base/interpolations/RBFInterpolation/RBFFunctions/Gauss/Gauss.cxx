#include <Gauss.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(Gauss, 0);
	addToRunTimeSelectionTable(RBFFunction, Gauss, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Gauss::Gauss(const scalar radius)
	:
	RBFFunction(),
	radius_(radius)
{}


tnbLib::Gauss::Gauss(const dictionary& dict)
	:
	RBFFunction(),
	radius_(readScalar(dict.lookup("radius")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::Gauss::~Gauss()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::Gauss::weights
(
	const vectorField& controlPoints,
	const vector& dataPoint
) const
{
	// Algorithmic improvement, Matteo Lombardi.  21/Mar/2011
	scalarField sqrDist = magSqr(controlPoints - dataPoint);

	return tnbLib::exp(-sqr(radius_)*sqrDist);
}


// ************************************************************************* //