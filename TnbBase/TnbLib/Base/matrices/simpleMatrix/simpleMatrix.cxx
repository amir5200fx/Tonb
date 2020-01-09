#include <simpleMatrix.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::simpleMatrix<Type>::simpleMatrix(const label mSize)
	:
	scalarSquareMatrix(mSize),
	source_(mSize)
{}


template<class Type>
tnbLib::simpleMatrix<Type>::simpleMatrix
(
	const label mSize,
	const scalar coeffVal,
	const Type& sourceVal
)
	:
	scalarSquareMatrix(mSize, coeffVal),
	source_(mSize, sourceVal)
{}


template<class Type>
tnbLib::simpleMatrix<Type>::simpleMatrix
(
	const scalarSquareMatrix& matrix,
	const Field<Type>& source
)
	:
	scalarSquareMatrix(matrix),
	source_(source)
{}


template<class Type>
tnbLib::simpleMatrix<Type>::simpleMatrix(Istream& is)
	:
	scalarSquareMatrix(is),
	source_(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::Field<Type> tnbLib::simpleMatrix<Type>::solve() const
{
	// Since matrix and source are trashed during solution,
	// a copy is made.  HJ, 23/Dec/2008
	scalarSquareMatrix tmpMatrix = *this;
	Field<Type> sourceSol = source_;

	scalarSquareMatrix::solve(tmpMatrix, sourceSol);

	return sourceSol;
}


template<class Type>
tnbLib::Field<Type> tnbLib::simpleMatrix<Type>::LUsolve() const
{
	// Since matrix and source are trashed during solution,
	// a copy is made.  HJ, 23/Dec/2008
	scalarSquareMatrix luMatrix = *this;
	Field<Type> sourceSol = source_;

	scalarSquareMatrix::LUsolve(luMatrix, sourceSol);

	return sourceSol;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::simpleMatrix<Type>::operator=(const simpleMatrix<Type>& m)
{
	if (this == &m)
	{
		FatalErrorIn("simpleMatrix<Type>::operator=(const simpleMatrix<Type>&)")
			<< "Attempted assignment to self"
			<< abort(FatalError);
	}

	if (n() != m.n())
	{
		FatalErrorIn("simpleMatrix<Type>::operator=(const simpleMatrix<Type>&)")
			<< "Different size matrices"
			<< abort(FatalError);
	}

	if (source_.size() != m.source_.size())
	{
		FatalErrorIn("simpleMatrix<Type>::operator=(const simpleMatrix<Type>&)")
			<< "Different size source vectors"
			<< abort(FatalError);
	}

	scalarSquareMatrix::operator=(m);
	source_ = m.source_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Type>
tnbLib::simpleMatrix<Type> tnbLib::operator+
(
	const simpleMatrix<Type>& m1,
	const simpleMatrix<Type>& m2
	)
{
	return simpleMatrix<Type>
		(
			static_cast<const scalarSquareMatrix&>(m1)
			+ static_cast<const scalarSquareMatrix&>(m2),
			m1.source_ + m2.source_
			);
}


template<class Type>
tnbLib::simpleMatrix<Type> tnbLib::operator-
(
	const simpleMatrix<Type>& m1,
	const simpleMatrix<Type>& m2
	)
{
	return simpleMatrix<Type>
		(
			static_cast<const scalarSquareMatrix&>(m1)
			- static_cast<const scalarSquareMatrix&>(m2),
			m1.source_ - m2.source_
			);
}


template<class Type>
tnbLib::simpleMatrix<Type> tnbLib::operator*
(
	const scalar s,
	const simpleMatrix<Type>& m
	)
{
	return simpleMatrix<Type>(s*m.matrix_, s*m.source_);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Type>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const simpleMatrix<Type>& m)
{
	os << static_cast<const scalarSquareMatrix&>(m) << nl << m.source_;
	return os;
}


// ************************************************************************* //