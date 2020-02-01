#include <fileName.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::fileName::fileName(Istream& is)
	:
	string(is)
{
	stripInvalid();
}


tnbLib::Istream& tnbLib::operator>>(Istream& is, fileName& fn)
{
	fileName fName(is);

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, fileName&)");

	fn = fName;

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const fileName& fn)
{
	os.write(fn);
	os.check("Ostream& operator<<(Ostream&, const fileName&)");
	return os;
}


// ************************************************************************* //