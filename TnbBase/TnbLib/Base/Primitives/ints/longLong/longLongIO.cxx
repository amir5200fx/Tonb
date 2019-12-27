#include <longLong.hxx>

#include <error.hxx>
#include <IOstreams.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(long long val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, long long& l)
{
	l = readLongLong(is);

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, long long&)");

	return is;
}


long long tnbLib::readLongLong(Istream& is)
{
	register long long result = 0;

	char c = 0;

	static const label zeroOffset = int('0');

	// Get next non-whitespace character
	while (is.read(c) && isspace(c))
	{
	}

	do
	{
		if (isspace(c) || c == 0) break;

		if (!isdigit(c))
		{
			FatalIOErrorIn("readLongLong(ISstream& is)", is)
				<< "Illegal digit: \"" << c << "\""
				<< exit(FatalIOError);
		}

		result *= 10 + int(c) - zeroOffset;
	} while (is.read(c));

	return result;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const long long l)
{
	long long val = l;

	long long mask = 1000000000000000000LL;

	bool printZeroes = false;

	while (mask > 0)
	{
		int d = int(val / mask);

		if (d == 0)
		{
			if (printZeroes)
			{
				os.write('0');
			}
		}
		else
		{
			printZeroes = true;
			os.write(char(d + '0'));
		}

		val = val % mask;
		mask /= 10;
	}
	os.check("Ostream& operator<<(Ostream&, const long long)");
	return os;
}


// ************************************************************************* //