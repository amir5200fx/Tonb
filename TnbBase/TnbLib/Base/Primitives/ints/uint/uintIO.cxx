#include <uint.hxx>

#include <error.hxx>
#include <IOstreams.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const unsigned int val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, unsigned int& i)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isLabel())
	{
		i = static_cast<unsigned int>(t.labelToken());
	}
	else
	{
		is.setBad();
		FatalIOErrorIn("operator>>(Istream&, unsigned int&)", is)
			<< "wrong token type - expected unsigned int found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, unsigned int&)");

	return is;
}


unsigned int tnbLib::readUint(Istream& is)
{
	unsigned int val;
	is >> val;

	return val;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const unsigned int i)
{
	os.write(label(i));
	os.check("Ostream& operator<<(Ostream&, const unsigned int)");
	return os;
}


// ************************************************************************* //