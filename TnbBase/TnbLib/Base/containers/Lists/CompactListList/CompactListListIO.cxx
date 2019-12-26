#include <CompactListList.hxx>

#include <Istream.hxx>

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<class T>
tnbLib::CompactListList<T>::CompactListList(Istream& is)
{
	operator>>(is, *this);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class T>
tnbLib::Istream& tnbLib::operator>>(Istream& is, CompactListList<T>& lst)
{
	is >> lst.offsets_ >> lst.m_;
	return is;
}


template<class T>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const CompactListList<T>& lst)
{
	os << lst.offsets_ << lst.m_;
	return os;
}


// ************************************************************************* //