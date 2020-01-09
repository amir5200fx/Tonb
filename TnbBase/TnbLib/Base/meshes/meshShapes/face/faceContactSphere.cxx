#include <face.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::face::contactSphereDiameter
(
	const point& p,
	const vector& n,
	const pointField& meshPoints
) const
{
	vector n1 = n / (tnbLib::mag(n) + SMALL);
	vector n2 = normal(meshPoints);

	n2 /= tnbLib::mag(n2) + SMALL;

	return 2 * ((centre(meshPoints) - p) & n2) / ((n1 & n2) - 1.0);
}


// ************************************************************************* //