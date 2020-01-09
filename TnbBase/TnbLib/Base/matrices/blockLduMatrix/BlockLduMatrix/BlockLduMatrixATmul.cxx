#include <BlockLduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::BlockLduMatrix<Type>::Amul
(
	TypeField& Ax,
	const TypeField& x
) const
{
	Ax = pTraits<Type>::zero;

	// Note: changed order of interface update: init after core
	// HJ, 14/Mar/2016

	AmulCore(Ax, x);

	// Initialise the update of coupled interfaces
	initInterfaces(coupleUpper_, Ax, x);

	// Update coupled interfaces
	updateInterfaces(coupleUpper_, Ax, x);
}


template<class Type>
void tnbLib::BlockLduMatrix<Type>::AmulCore
(
	TypeField& Ax,
	const TypeField& x
) const
{
	typedef typename TypeCoeffField::scalarTypeField scalarTypeField;
	typedef typename TypeCoeffField::linearTypeField linearTypeField;
	typedef typename TypeCoeffField::squareTypeField squareTypeField;

	const unallocLabelList& u = lduAddr().upperAddr();
	const unallocLabelList& l = lduAddr().lowerAddr();

	const TypeCoeffField& Diag = this->diag();
	const TypeCoeffField& Upper = this->upper();

	// Create multiplication function object
	typename BlockCoeff<Type>::multiply mult;

	// Diagonal multiplication, no indirection
	multiply(Ax, Diag, x);

	// Lower multiplication

	if (symmetric())
	{
		if (Upper.activeType() == blockCoeffBase::SCALAR)
		{
			const scalarTypeField& activeUpper = Upper.asScalar();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				Ax[u[coeffI]] += mult(activeUpper[coeffI], x[l[coeffI]]);
			}
		}
		else if (Upper.activeType() == blockCoeffBase::LINEAR)
		{
			const linearTypeField& activeUpper = Upper.asLinear();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				Ax[u[coeffI]] += mult(activeUpper[coeffI], x[l[coeffI]]);
			}
		}
		else if (Upper.activeType() == blockCoeffBase::SQUARE)
		{
			const squareTypeField& activeUpper = Upper.asSquare();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				// Use transpose upper coefficient
				Ax[u[coeffI]] +=
					mult(activeUpper[coeffI].T(), x[l[coeffI]]);
			}
		}
	}
	else // Asymmetric matrix
	{
		const TypeCoeffField& Lower = this->lower();

		if (Lower.activeType() == blockCoeffBase::SCALAR)
		{
			const scalarTypeField& activeLower = Lower.asScalar();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				Ax[u[coeffI]] += mult(activeLower[coeffI], x[l[coeffI]]);
			}
		}
		else if (Lower.activeType() == blockCoeffBase::LINEAR)
		{
			const linearTypeField& activeLower = Lower.asLinear();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				Ax[u[coeffI]] += mult(activeLower[coeffI], x[l[coeffI]]);
			}
		}
		else if (Lower.activeType() == blockCoeffBase::SQUARE)
		{
			const squareTypeField& activeLower = Lower.asSquare();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				Ax[u[coeffI]] += mult(activeLower[coeffI], x[l[coeffI]]);
			}
		}
	}

	// Upper multiplication

	if (Upper.activeType() == blockCoeffBase::SCALAR)
	{
		const scalarTypeField& activeUpper = Upper.asScalar();

		for (register label coeffI = 0; coeffI < u.size(); coeffI++)
		{
			Ax[l[coeffI]] += mult(activeUpper[coeffI], x[u[coeffI]]);
		}
	}
	else if (Upper.activeType() == blockCoeffBase::LINEAR)
	{
		const linearTypeField& activeUpper = Upper.asLinear();

		for (register label coeffI = 0; coeffI < u.size(); coeffI++)
		{
			Ax[l[coeffI]] += mult(activeUpper[coeffI], x[u[coeffI]]);
		}
	}
	else if (Upper.activeType() == blockCoeffBase::SQUARE)
	{
		const squareTypeField& activeUpper = Upper.asSquare();

		for (register label coeffI = 0; coeffI < u.size(); coeffI++)
		{
			Ax[l[coeffI]] += mult(activeUpper[coeffI], x[u[coeffI]]);
		}
	}
}


template<class Type>
void tnbLib::BlockLduMatrix<Type>::Tmul
(
	TypeField& Ax,
	const TypeField& x
) const
{
	Ax = pTraits<Type>::zero;

	TmulCore(Ax, x);

	// Note: changed order of interface update: init after core
	// HJ, 14/Mar/2016

	// Initialise the update of coupled interfaces
	initInterfaces(coupleLower_, Ax, x);

	// Update coupled interfaces
	updateInterfaces(coupleLower_, Ax, x);
}


template<class Type>
void tnbLib::BlockLduMatrix<Type>::TmulCore
(
	TypeField& Tx,
	const TypeField& x
) const
{
	typedef typename TypeCoeffField::scalarTypeField scalarTypeField;
	typedef typename TypeCoeffField::linearTypeField linearTypeField;
	typedef typename TypeCoeffField::squareTypeField squareTypeField;

	const unallocLabelList& u = lduAddr().upperAddr();
	const unallocLabelList& l = lduAddr().lowerAddr();

	const TypeCoeffField& Diag = this->diag();
	const TypeCoeffField& Upper = this->upper();

	// Diagonal multiplication, no indirection
	multiply(Tx, Diag, x);

	// Upper multiplication

	if (Upper.activeType() == blockCoeffBase::SCALAR)
	{
		const scalarTypeField& activeUpper = Upper.asScalar();

		for (register label coeffI = 0; coeffI < u.size(); coeffI++)
		{
			Tx[u[coeffI]] += mult(activeUpper[coeffI], x[l[coeffI]]);
		}
	}
	else if (Upper.activeType() == blockCoeffBase::LINEAR)
	{
		const linearTypeField& activeUpper = Upper.asLinear();

		for (register label coeffI = 0; coeffI < u.size(); coeffI++)
		{
			Tx[u[coeffI]] += mult(activeUpper[coeffI], x[l[coeffI]]);
		}
	}
	else if (Upper.activeType() == blockCoeffBase::SQUARE)
	{
		const squareTypeField& activeUpper = Upper.asSquare();

		for (register label coeffI = 0; coeffI < u.size(); coeffI++)
		{
			// Bug fix: Missing transpose. VV, 31/Aug/2015.
			Tx[u[coeffI]] += mult(activeUpper[coeffI].T(), x[l[coeffI]]);
		}
	}

	// Lower multiplication

	if (symmetric())
	{
		if (Upper.activeType() == blockCoeffBase::SCALAR)
		{
			const scalarTypeField& activeUpper = Upper.asScalar();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				Tx[l[coeffI]] += mult(activeUpper[coeffI], x[u[coeffI]]);
			}
		}
		else if (Upper.activeType() == blockCoeffBase::LINEAR)
		{
			const linearTypeField& activeUpper = Upper.asLinear();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				Tx[l[coeffI]] += mult(activeUpper[coeffI], x[u[coeffI]]);
			}
		}
		else if (Upper.activeType() == blockCoeffBase::SQUARE)
		{
			const squareTypeField& activeUpper = Upper.asSquare();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				// Use transpose upper coefficient
				Tx[l[coeffI]] +=
					mult(activeUpper[coeffI].T(), x[u[coeffI]]);
			}
		}
	}
	else // Asymmetric matrix
	{
		const TypeCoeffField& Lower = this->lower();

		if (Lower.activeType() == blockCoeffBase::SCALAR)
		{
			const scalarTypeField& activeLower = Lower.asScalar();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				Tx[l[coeffI]] += mult(activeLower[coeffI], x[u[coeffI]]);
			}
		}
		else if (Lower.activeType() == blockCoeffBase::LINEAR)
		{
			const linearTypeField& activeLower = Lower.asLinear();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				Tx[l[coeffI]] += mult(activeLower[coeffI], x[u[coeffI]]);
			}
		}
		else if (Lower.activeType() == blockCoeffBase::SQUARE)
		{
			const squareTypeField& activeLower = Lower.asSquare();

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				// Bug fix: Missing transpose. VV, 31/Aug/2015.
				Tx[l[coeffI]] += mult(activeLower[coeffI].T(), x[u[coeffI]]);
			}
		}
	}
}


template<class Type>
void tnbLib::BlockLduMatrix<Type>::segregateB
(
	TypeField& sMul,
	const TypeField& x
) const
{
	typedef typename TypeCoeffField::linearType linearType;
	typedef typename TypeCoeffField::squareType squareType;

	typedef typename TypeCoeffField::linearTypeField linearTypeField;
	typedef typename TypeCoeffField::squareTypeField squareTypeField;

	const unallocLabelList& u = lduAddr().upperAddr();
	const unallocLabelList& l = lduAddr().lowerAddr();

	// Diagonal multiplication
	if (thereIsDiag())
	{
		if (diag().activeType() == blockCoeffBase::SQUARE)
		{
			const squareTypeField& activeDiag = this->diag().asSquare();
			linearTypeField lf(activeDiag.size());
			squareTypeField sf(activeDiag.size());

			// Expand and contract
			contractLinear(lf, activeDiag);
			expandLinear(sf, lf);

			sMul -= (activeDiag - sf) & x;
		}
	}

	// Lower multiplication

	if (thereIsLower())
	{
		if (lower().activeType() == blockCoeffBase::SQUARE)
		{
			const squareTypeField& activeLower = this->lower().asSquare();

			// Auxiliary variables used in expand/contract
			linearType lt;
			squareType st;

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				contractLinear(lt, activeLower[coeffI]);
				expandLinear(st, lt);

				sMul[u[coeffI]] -= (activeLower[coeffI] - st) & x[l[coeffI]];
			}
		}
	}

	// Upper multiplication

	if (thereIsUpper())
	{
		if (upper().activeType() == blockCoeffBase::SQUARE)
		{
			const squareTypeField& activeUpper = this->upper().asSquare();

			// Auxiliary variables used in expand/contract
			linearType lt;
			squareType st;

			for (register label coeffI = 0; coeffI < u.size(); coeffI++)
			{
				contractLinear(lt, activeUpper[coeffI]);
				expandLinear(st, lt);

				sMul[l[coeffI]] -= (activeUpper[coeffI] - st) & x[u[coeffI]];
			}

			// If the matrix is symmetric, the lower triangular product
			// is also needed
			if (symmetric())
			{
				for (register label coeffI = 0; coeffI < u.size(); coeffI++)
				{
					// Use transpose upper coefficient
					contractLinear(lt, activeUpper[coeffI]);
					expandLinear(st, lt);
					sMul[u[coeffI]] -=
						(activeUpper[coeffI].T() - st) & x[l[coeffI]];
				}
			}
		}
	}
}


// ************************************************************************* //