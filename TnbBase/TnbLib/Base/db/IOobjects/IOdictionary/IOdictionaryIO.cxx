#include <IOdictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

bool tnbLib::IOdictionary::readData(Istream& is)
{
	is >> *this;
	return !is.bad();
}


bool tnbLib::IOdictionary::writeData(Ostream& os) const
{
	dictionary::write(os, false);
	return os.good();
}

// ************************************************************************* //
