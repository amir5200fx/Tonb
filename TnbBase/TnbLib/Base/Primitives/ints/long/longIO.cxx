#include <long.hxx>

#include <error.hxx>
#include <IOstreams.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(long val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, long& l)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isLabel())
	{
		l = long(t.labelToken());
	}
	else
	{
		is.setBad();
		FatalIOErrorIn("operator>>(Istream&, long&)", is)
			<< "wrong token type - expected long found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, long&)");

	return is;
}


long tnbLib::readLong(Istream& is)
{
	long val;
	is >> val;

	return val;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const long l)
{
	os.write(label(l));
	os.check("Ostream& operator<<(Ostream&, const long)");
	return os;
}


// ************************************************************************* //