#include <septernion.hxx>

#include <IOstreams.hxx>
#include <OStringStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::septernion::typeName = "septernion";
const tnbLib::septernion tnbLib::septernion::zero(vector::zero, quaternion::zero);
const tnbLib::septernion tnbLib::septernion::I(vector::zero, quaternion::I);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::septernion::septernion(Istream& is)
{
	operator>>(is, *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const septernion& s)
{
	OStringStream buf;
	buf << '(' << s.t() << ',' << s.r() << ')';
	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, septernion& s)
{
	// Read beginning of septernion
	is.readBegin("septernion");

	is >> s.t() >> s.r();

	// Read end of septernion
	is.readEnd("septernion");

	// Check state of Istream
	is.check("operator>>(Istream&, septernion&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const septernion& s)
{
	os << token::BEGIN_LIST
		<< s.t() << token::SPACE << s.r()
		<< token::END_LIST;

	return os;
}


// ************************************************************************* //