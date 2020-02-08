#include <dimensionSet.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dimensionSet::dimensionSet(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, dimensionSet& dset)
{
	// Read begining of dimensionSet
	if (token(is) != token::BEGIN_SQR)
	{
		Info << "expected a " << token::BEGIN_SQR << " in dimensionSet"
			<< endl << "in stream " << is.info() << endl;
	}

	// Read first five dimensions
	for (int Dimension = 0; Dimension < dimensionSet::CURRENT; Dimension++)
	{
		is >> dset.exponents_[Dimension];
	}

	// Read next token
	token nextToken(is);

	// If next token is another number
	// read last two dimensions
	// and then read another token for the end of the dimensionSet
	if (nextToken.isNumber())
	{
		dset.exponents_[dimensionSet::CURRENT] = nextToken.number();
		is >> dset.exponents_[dimensionSet::LUMINOUS_INTENSITY];
		is >> nextToken;
	}
	else
	{
		dset.exponents_[dimensionSet::CURRENT] = 0;
		dset.exponents_[dimensionSet::LUMINOUS_INTENSITY] = 0;
	}

	// Check end of dimensionSet
	if (nextToken != token::END_SQR)
	{
		Info << "expected a " << token::END_SQR << " in dimensionSet"
			<< endl << "in stream " << is.info() << endl;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, dimensionSet&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const dimensionSet& dset)
{
	os << token::BEGIN_SQR;

	for (int Dimension = 0; Dimension < dimensionSet::nDimensions - 1; Dimension++)
	{
		os << dset.exponents_[Dimension] << token::SPACE;
	}
	os << dset.exponents_[dimensionSet::nDimensions - 1] << token::END_SQR;

	// Check state of Ostream
	os.check("Ostream& operator<<(Ostream&, const dimensionSet&)");

	return os;
}


// ************************************************************************* //