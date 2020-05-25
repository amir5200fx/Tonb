#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool tnbLib::speciesTable::contains(const word& specieName) const
{
	return specieIndices_.found(specieName);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline const tnbLib::word& tnbLib::speciesTable::operator[]
(
	const label specieIndex
	) const
{
	return wordList::operator[](specieIndex);
}


inline tnbLib::label tnbLib::speciesTable::operator[](const word& specieName) const
{
	return specieIndices_[specieName];
}


// ************************************************************************* //