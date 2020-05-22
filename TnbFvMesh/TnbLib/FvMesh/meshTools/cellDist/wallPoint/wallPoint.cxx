#include <wallPoint.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::point tnbLib::wallPoint::greatPoint(GREAT, GREAT, GREAT);


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream& os, const tnbLib::wallPoint& wDist)
{
	return os << wDist.origin() << wDist.distSqr();
}

tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream& is, tnbLib::wallPoint& wDist)
{
	return is >> wDist.origin() >> wDist.distSqr();
}

// ************************************************************************* //