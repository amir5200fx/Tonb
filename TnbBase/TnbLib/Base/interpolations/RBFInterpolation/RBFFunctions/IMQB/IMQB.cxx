#include <IMQB.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(IMQB, 0);
	addToRunTimeSelectionTable(RBFFunction, IMQB, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IMQB::IMQB(const scalar radius)
	:
	RBFFunction(),
	radius_(radius)
{}


// Construct from dictionary
tnbLib::IMQB::IMQB(const dictionary& dict)
	:
	RBFFunction(),
	radius_(readScalar(dict.lookup("radius")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::IMQB::~IMQB()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::IMQB::weights
(
	const vectorField& controlPoints,
	const vector& dataPoint
) const
{
	// Algorithmic improvement, Matteo Lombardi.  21/Mar/2011
	scalarField sqrDist = magSqr(controlPoints - dataPoint);

	return 1 / sqrt(sqrDist + sqr(radius_));
}


// ************************************************************************* //