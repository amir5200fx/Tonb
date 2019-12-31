#include <UPtrList.hxx>

#include <Ostream.hxx>

// * * * * * * * * * * * * * * * Ostream Operators * * * * * * * * * * * * * //

template<class T>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const UPtrList<T>& L)
{
	// Write size and start delimiter
	os << nl << L.size() << nl << token::BEGIN_LIST;

	// Write contents
	forAll(L, i)
	{
		os << nl << L[i];
	}

	// Write end delimiter
	os << nl << token::END_LIST << nl;

	// Check state of IOstream
	os.check("Ostream& operator<<(Ostream&, const UPtrList&)");

	return os;
}


// ************************************************************************* //