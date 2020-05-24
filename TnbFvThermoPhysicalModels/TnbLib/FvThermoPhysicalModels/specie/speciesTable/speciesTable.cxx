#include <speciesTable.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::speciesTable::setIndices()
{
	forAll(*this, i)
	{
		specieIndices_.insert(wordList::operator[](i), i);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from list of specie names
tnbLib::speciesTable::speciesTable(const wordList& specieNames)
	:
	wordList(specieNames)
{
	setIndices();
}


// Construct from number of species and list of specie names
tnbLib::speciesTable::speciesTable(const label nSpecies, const char** specieNames)
	:
	wordList(nSpecies)
{
	forAll(*this, i)
	{
		wordList::operator[](i) = specieNames[i];
	}

	setIndices();
}


// Construct from Istream
tnbLib::speciesTable::speciesTable(Istream& is)
	:
	wordList(is)
{
	setIndices();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, speciesTable& st)
{
	is >> static_cast<wordList&>(st);
	st.setIndices();

	return is;
}

// ************************************************************************* //