#include <readHexLabel.hxx>

#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::label tnbLib::readHexLabel(ISstream& is)
{
	// Takes into account that 'a' (or 'A') is 10
	static const label alphaOffset = toupper('A') - 10;
	// Takes into account that '0' is 0
	static const label zeroOffset = int('0');

	char c = 0;

	// Get next non-whitespace character
	while (is.get(c) && isspace(c))
	{
	}

	register label result = 0;
	do
	{
		if (isspace(c) || c == 0) break;

		if (!isxdigit(c))
		{
			FatalIOErrorIn("readHexLabel(ISstream&)", is)
				<< "Illegal hex digit: '" << c << "'"
				<< exit(FatalIOError);
		}

		result *= 16;

		if (isdigit(c))
		{
			result += int(c) - zeroOffset;
		}
		else
		{
			result += toupper(c) - alphaOffset;
		}
	} while (is.get(c));

	return result;
}


// ************************************************************************* //