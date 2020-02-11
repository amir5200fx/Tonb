#include <fvBlockMatrix.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fvBlockMatrix<Type>::negate()
{
	BlockLduSystem<Type, Type>::negate();
	psi_.negate();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fvBlockMatrix<Type>::operator=
(
	const fvBlockMatrix<Type>& bxs
	)
{
	if (this == &bxs)
	{
		FatalErrorIn
		(
			"void fvBlockMatrix<Type>::operator="
			"(const fvBlockMatrix<Type>& bs)"
		) << "attempted assignment to self"
			<< abort(FatalError);
	}

	BlockLduSystem<Type, Type>::operator=(bxs);
	psi_ = bxs.psi();
}


template<class Type>
void tnbLib::fvBlockMatrix<Type>::operator+=
(
	const fvBlockMatrix<Type>& bxs
	)
{
	BlockLduSystem<Type, Type>::operator+=(bxs);
	psi_ += bxs.psi();
}

template<class Type>
void tnbLib::fvBlockMatrix<Type>::operator-=
(
	const fvBlockMatrix<Type>& bxs
	)
{
	BlockLduSystem<Type, Type>::operator-=(bxs);
	psi_ -= bxs.psi();
}

template<class Type>
void tnbLib::fvBlockMatrix<Type>::operator*=
(
	const scalarField& sf
	)
{
	BlockLduSystem<Type, Type>::operator*=(sf);
	psi_ *= sf;
}

template<class Type>
void tnbLib::fvBlockMatrix<Type>::operator*=
(
	const scalar s
	)
{
	BlockLduSystem<Type, Type>::operator*=(s);
	psi_ *= s;
}


// ************************************************************************* //