#include <FRWGraph.hxx>

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class T, tnbLib::label width>
tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::FRWGraph<T, width>& DL
	)
{
	os << DL.size() << "(" << endl;
	for (register label i = 0; i < DL.size(); ++i)
	{
		os << width << "(";
		for (label j = 0; j < width; ++j)
			os << DL(i, j) << " " << endl;
		os << ")" << endl;
	}
	os << ")";
	return os;
}

/*
template<class T, tnbLib::label width>
tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::FRWGraph<T, width>& DL
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