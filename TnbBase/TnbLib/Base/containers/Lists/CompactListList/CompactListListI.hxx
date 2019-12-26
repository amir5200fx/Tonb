#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
tnbLib::CompactListList<T>::CompactListList()
{}


template<class T>
tnbLib::CompactListList<T>::CompactListList
(
	const label nRows,
	const label nData
)
	:
	offsets_(nRows, 0),
	m_(nData)
{}


template<class T>
tnbLib::CompactListList<T>::CompactListList
(
	const label nRows,
	const label nData,
	const T& t
)
	:
	offsets_(nRows, 0),
	m_(nData, t)
{}


template<class T>
tnbLib::autoPtr<tnbLib::CompactListList<T> >
tnbLib::CompactListList<T>::clone() const
{
	return autoPtr<CompactListList<T> >(new CompactListList<T>(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
const tnbLib::CompactListList<T>& tnbLib::CompactListList<T>::null()
{
	return *reinterpret_cast<CompactListList<T>*>(0);
}


template<class T>
tnbLib::label tnbLib::CompactListList<T>::size() const
{
	return offsets_.size();
}


template<class T>
bool tnbLib::CompactListList<T>::empty() const
{
	return offsets_.empty();
}


template<class T>
const tnbLib::List<tnbLib::label>& tnbLib::CompactListList<T>::offsets() const
{
	return offsets_;
}


template<class T>
tnbLib::List<tnbLib::label>& tnbLib::CompactListList<T>::offsets()
{
	return offsets_;
}


template<class T>
const tnbLib::List<T>& tnbLib::CompactListList<T>::m() const
{
	return m_;
}


template<class T>
tnbLib::List<T>& tnbLib::CompactListList<T>::m()
{
	return m_;
}


template<class T>
tnbLib::label tnbLib::CompactListList<T>::index
(
	const label i,
	const label j
) const
{
	if (i == 0)
	{
		return j;
	}
	else
	{
		return offsets_[i - 1] + j;
	}
}


template<class T>
tnbLib::label tnbLib::CompactListList<T>::whichRow(const label i) const
{
	if (i < 0 || i >= m_.size())
	{
		FatalErrorIn
		(
			"CompactListList<T>::whichRow(const label) const"
		) << "Index " << i << " outside 0.." << m_.size()
			<< abort(FatalError);
	}

	forAll(offsets_, rowI)
	{
		if (i < offsets_[rowI])
		{
			return rowI;
		}
	}

	return -1;
}


template<class T>
tnbLib::label tnbLib::CompactListList<T>::whichColumn
(
	const label row,
	const label i
) const
{
	return i - index(row, 0);
}


template<class T>
tnbLib::Xfer<tnbLib::CompactListList<T> > tnbLib::CompactListList<T>::xfer()
{
	return xferMove(*this);
}


template<class T>
void tnbLib::CompactListList<T>::resize(const label nRows)
{
	this->setSize(nRows);
}


template<class T>
void tnbLib::CompactListList<T>::resize
(
	const label nRows,
	const label nData
)
{
	this->setSize(nRows, nData);
}


template<class T>
void tnbLib::CompactListList<T>::resize
(
	const label nRows,
	const label nData,
	const T& t
)
{
	this->setSize(nRows, nData, t);
}


template<class T>
void tnbLib::CompactListList<T>::resize(const UList<label>& rowSizes)
{
	this->setSize(rowSizes);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
tnbLib::UList<T> tnbLib::CompactListList<T>::operator[]
(
	const label i
	)
{
	if (i == 0)
	{
		return UList<T>(m_.begin(), offsets_[i]);
	}
	else
	{
		return UList<T>(&m_[offsets_[i - 1]], offsets_[i] - offsets_[i - 1]);
	}
}


template<class T>
const tnbLib::UList<T> tnbLib::CompactListList<T>::operator[]
(
	const label i
	) const
{
	if (i == 0)
	{
		return UList<T>(m_.begin(), offsets_[i]);
	}
	else
	{
		return UList<T>(&m_[offsets_[i - 1]], offsets_[i] - offsets_[i - 1]);
	}
}


template<class T>
T& tnbLib::CompactListList<T>::operator()
(
	const label i,
	const label j
	)
{
	return m_[index(i, j)];
}


template<class T>
const T& tnbLib::CompactListList<T>::operator()
(
	const label i,
	const label j
	) const
{
	return m_[index(i, j)];
}


template<class T>
void tnbLib::CompactListList<T>::operator=(const T& t)
{
	m_ = t;
}


// ************************************************************************* //