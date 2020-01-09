#include <TPS.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(TPS, 0);
	addToRunTimeSelectionTable(RBFFunction, TPS, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::TPS::TPS(const scalar radius)
	:
	RBFFunction(),
	radius_(radius)
{}


tnbLib::TPS::TPS(const dictionary& dict)
	:
	RBFFunction(),
	radius_(readScalar(dict.lookup("radius")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::TPS::~TPS()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::TPS::weights
(
	const vectorField& controlPoints,
	const vector& dataPoint
) const
{
	scalarField dist = mag(controlPoints - dataPoint);
	scalarField RBF(dist.size());

	forAll(RBF, i)
	{
		if (dist[i] > SMALL)
		{
			RBF[i] = sqr(dist[i])*log(dist[i]);
		}
		else
		{
			RBF[i] = 0.0;
		}
	}

	return RBF;
}


// ************************************************************************* //