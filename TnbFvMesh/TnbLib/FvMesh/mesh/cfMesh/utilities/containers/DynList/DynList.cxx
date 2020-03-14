#include <DynList.hxx>

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

// Construct from Istream
template<class T, tnbLib::label staticSize>
tnbLib::DynList<T, staticSize>::DynList(Istream& is)
	:
	UList<T>(),
	nextFree_(0)
{
	FatalErrorIn
	(
		"template<class T, tnbLib::label staticSize>"
		"\nFoam::DynList<T, staticSize>::DynList(Istream& is)"
	) << "Not implemented" << exit(FatalError);

	List<T> helper(is);

	nextFree_ = helper.size();
	UList<T>::swap(helper);
}


template<class T, tnbLib::label staticSize>
tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::DynList<T, staticSize>& DL
	)
{
	UList<T> helper(const_cast<T*>(DL.begin()), DL.nextFree_);
	os << helper;

	return os;
}


template<class T, tnbLib::label staticSize>
tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::DynList<T, staticSize>& DL
	)
{
	FatalErrorIn
	(
		"template<class T, tnbLib::label staticSize>"
		"\nFoam::Istream& tnbLib::operator>>"
		"(tnbLib::Istream& is, tnbLib::DynList<T, staticSize>& DL)"
	) << "Not implemented" << exit(FatalError);

	is >> static_cast<List<T>&>(DL);
	DL.nextFree_ = DL.List<T>::size();

	return is;
}


// ************************************************************************* //
