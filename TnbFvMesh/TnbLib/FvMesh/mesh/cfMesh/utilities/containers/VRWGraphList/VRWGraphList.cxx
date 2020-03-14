#include <VRWGraphList.hxx>

#include <token.hxx>
#include <labelList.hxx>

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::VRWGraphList& DL
	)
{
	os << DL.size() << nl << token::BEGIN_LIST;

	for (register label i = 0; i < DL.size(); ++i)
	{
		os << nl << DL[i];
	}

	os << nl << token::END_LIST;
	return os;
}

/*
template<class T, tnbLib::label width>
tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::VRWGraphList<T, width>& DL
)
{
	label size;
	T e;
	is >> size;
	DL.setSize(size);
	for(IndexType i=0;i<size;++i)
	{
		is >> e;
		DL[i] = e;
	}

	return is;
}
*/

// ************************************************************************* //
