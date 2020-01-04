#include <W2.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <dictionary.hxx>
#include <scalarField.hxx>


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(W2, 0);
	addToRunTimeSelectionTable(RBFFunction, W2, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::W2::W2(const scalar radius)
	:
	RBFFunction(),
	radius_(radius)
{}


tnbLib::W2::W2(const dictionary& dict)
	:
	RBFFunction(),
	radius_(readScalar(dict.lookup("radius")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::W2::~W2()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::W2::weights
(
	const vectorField& controlPoints,
	const vector& dataPoint
) const
{
	scalarField dist = mag(controlPoints - dataPoint);

	scalarField RBF(dist.size());

	RBF = neg(dist - radius_)*
		tnbLib::max(pow4(1 - (dist / radius_)), scalar(0))*(1 + 4 * (dist / radius_));

	return RBF;
}

// ************************************************************************* //
