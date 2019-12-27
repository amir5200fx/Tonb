#include <int.hxx>

#include <error.hxx>
#include <IOstreams.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const int val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, int& i)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isLabel())
	{
		i = int(t.labelToken());
	}
	else
	{
		is.setBad();
		FatalIOErrorIn("operator>>(Istream&, int&)", is)
			<< "wrong token type - expected int found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, int&)");

	return is;
}


int tnbLib::readInt(Istream& is)
{
	int val;
	is >> val;

	return val;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const int i)
{
	os.write(label(i));
	os.check("Ostream& operator<<(Ostream&, const int)");
	return os;
}


// ************************************************************************* //
