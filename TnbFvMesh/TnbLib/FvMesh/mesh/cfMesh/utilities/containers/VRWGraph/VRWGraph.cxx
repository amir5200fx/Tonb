#include <VRWGraph.hxx>

#include <token.hxx>
#include <labelList.hxx>

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::VRWGraph& DL
	)
{
	os << DL.size() << nl << token::BEGIN_LIST;

	for (register label i = 0; i < DL.size(); ++i)
	{
		os << nl << DL.sizeOfRow(i) << token::BEGIN_LIST;
		for (label j = 0; j < DL.sizeOfRow(i); ++j)
		{
			if (j > 0) os << token::SPACE;

			os << DL(i, j);
		}

		os << token::END_LIST;
	}

	os << nl << token::END_LIST;
	return os;
}

/*
template<class T, tnbLib::label width>
tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::VRWGraph<T, width>& DL
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

void tnbLib::VRWGraph::optimizeMemoryUsage()
{
	labelLongList newPosForNode(data_.size());
	label pos(0), nElements;
	nElements = data_.size();
	for (label elI = 0; elI < nElements; ++elI)
		if (data_[elI] != FREEENTRY)
		{
			newPosForNode[elI] = pos++;
		}
		else
		{
			newPosForNode[elI] = -1;
		}

	//- create new data
	for (label elI = 0; elI < nElements; ++elI)
		if ((newPosForNode[elI] != -1) && (newPosForNode[elI] < elI))
			data_[newPosForNode[elI]] = data_[elI];

	data_.setSize(pos);

	//- renumber rows
	nElements = rows_.size();
	for (label rowI = 0; rowI < nElements; ++rowI)
		if (rows_[rowI].start() != INVALIDROW)
			rows_[rowI].start() = newPosForNode[rows_[rowI].start()];
}

// ************************************************************************* //