#include <quaternion.hxx>

#include <IOstreams.hxx>
#include <OStringStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::quaternion::typeName = "quaternion";
const tnbLib::quaternion tnbLib::quaternion::zero(0, vector::zero);
const tnbLib::quaternion tnbLib::quaternion::I(1, vector::zero);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::quaternion::quaternion(Istream& is)
{
	operator>>(is, *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const quaternion& q)
{
	OStringStream buf;
	buf << '(' << q.w() << ',' << q.v() << ')';
	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, quaternion& q)
{
	// Read beginning of quaternion
	is.readBegin("quaternion");

	is >> q.w() >> q.v();

	// Read end of quaternion
	is.readEnd("quaternion");

	// Check state of Istream
	is.check("operator>>(Istream&, quaternion&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const quaternion& q)
{
	os << token::BEGIN_LIST
		<< q.w() << token::SPACE << q.v()
		<< token::END_LIST;

	return os;
}


// ************************************************************************* //