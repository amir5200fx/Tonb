#pragma once
template<class T, tnbLib::label width>
void tnbLib::FRWGraph<T, width>::checkIndex(const label i, const label j) const
{
	if ((i < 0) || (i >= nRows_))
	{
		FatalErrorIn
		(
			"void tnbLib::FRWGraph<T,width>::"
			"checkIndex(const label i, const label j) const"
		) << "Row index " << i
			<< " is not in range " << 0
			<< " and " << nRows_ << abort(FatalError);
	}

	if ((j < 0) || (j >= width))
		FatalErrorIn
		(
			"void tnbLib::FRWGraph<T,width>::"
			"checkIndex(const label i, const label j) const"
		) << "Column index " << j
		<< " is not in range " << 0
		<< " and " << width << abort(FatalError);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

//- Construct null
template<class T, tnbLib::label width>
inline tnbLib::FRWGraph<T, width>::FRWGraph()
	:
	data_(),
	nRows_(0)
{}

//- Construct given size
template<class T, tnbLib::label width>
inline tnbLib::FRWGraph<T, width>::FRWGraph
(
	const label s
)
	:
	data_(s * width),
	nRows_(s)
{}


//- Construct given size
template<class T, tnbLib::label width>
inline tnbLib::FRWGraph<T, width>::FRWGraph
(
	const label s,
	const T& t
)
	:
	data_(s * width, t),
	nRows_(s)
{}

template<class T, tnbLib::label width>
inline tnbLib::FRWGraph<T, width>::FRWGraph
(
	const FRWGraph<T, width>& ol
)
	:
	data_(ol.data_),
	nRows_(ol.nRows_)
{}

template<class T, tnbLib::label width>
inline tnbLib::FRWGraph<T, width>::~FRWGraph()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T, tnbLib::label width>
inline tnbLib::label tnbLib::FRWGraph<T, width>::size() const
{
	return nRows_;
}

template<class T, tnbLib::label width>
inline tnbLib::label tnbLib::FRWGraph<T, width>::sizeOfRow(const label rowI) const
{
	return width;
}

template<class T, tnbLib::label width>
inline void tnbLib::FRWGraph<T, width>::setSize(const label i)
{
	data_.setSize(i * width);
	nRows_ = i;
}

template<class T, tnbLib::label width>
inline void tnbLib::FRWGraph<T, width>::clear()
{
	data_.clear();
	nRows_ = 0;
}

template<class T, tnbLib::label width>
inline void tnbLib::FRWGraph<T, width>::appendFixedList
(
	const FixedList<T, width>& l
)
{
	forAll(l, elI)
		data_.append(l[elI]);
	++nRows_;
}

template<class T, tnbLib::label width>
inline void tnbLib::FRWGraph<T, width>::setRow
(
	const label rowI,
	const FixedList<T, width>& l
)
{
	const label start = rowI * width;
	forAll(l, elI)
		data_[start + elI] = l[elI];
}

template<class T, tnbLib::label width>
inline bool tnbLib::FRWGraph<T, width>::contains
(
	const label rowI,
	const T& e
) const
{
	const label start = rowI * width;
	for (register label i = 0; i < width; ++i)
		if (data_[start + i] == e)
			return true;

	return false;
}

template<class T, tnbLib::label width>
inline tnbLib::label tnbLib::FRWGraph<T, width>::containsAtPosition
(
	const label rowI,
	const T& e
) const
{
	const label start = rowI * width;
	for (register label i = 0; i < width; ++i)
		if (data_[start + i] == e)
			return i;

	return -1;
}

// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //
template<class T, tnbLib::label width>
inline const T& tnbLib::FRWGraph<T, width>::operator()
(
	const label i,
	const label j
	) const
{
#ifdef FULLDEBUG
	checkIndex(i, j);
#endif

	return data_[i * width + j];
}

template<class T, tnbLib::label width>
inline T& tnbLib::FRWGraph<T, width>::operator()
(
	const label i, const label j
	)
{
#ifdef FULLDEBUG
	checkIndex(i, j);
#endif

	return data_[i * width + j];
}

template<class T, tnbLib::label width>
inline void tnbLib::FRWGraph<T, width>::operator=
(
	const FRWGraph<T, width>& l
	)
{
	data_ = l.data_;
	nRows_ = l.nRows_;
}


// ************************************************************************* //