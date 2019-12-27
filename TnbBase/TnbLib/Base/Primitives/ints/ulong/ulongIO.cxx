#include <ulong.hxx>

#include <error.hxx>
#include <IOstreams.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const unsigned long val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, unsigned long& val)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isLabel())
	{
		val = static_cast<unsigned long>(t.labelToken());
	}
	else
	{
		is.setBad();
		FatalIOErrorIn("operator>>(Istream&, unsigned long&)", is)
			<< "wrong token type - expected unsigned long found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, unsigned long&)");

	return is;
}


unsigned long tnbLib::readUlong(Istream& is)
{
	unsigned long val;
	is >> val;

	return val;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const unsigned long val)
{
	os.write(label(val));
	os.check("Ostream& operator<<(Ostream&, const unsigned long)");
	return os;
}


// ************************************************************************* //