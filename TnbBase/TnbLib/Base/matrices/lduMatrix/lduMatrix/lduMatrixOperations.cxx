#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::lduMatrix::sumDiag()
{
	const scalarField& Lower = const_cast<const lduMatrix&>(*this).lower();
	const scalarField& Upper = const_cast<const lduMatrix&>(*this).upper();
	scalarField& Diag = diag();

	const unallocLabelList& l = lduAddr().lowerAddr();
	const unallocLabelList& u = lduAddr().upperAddr();

	for (register label odcI = 0; odcI < l.size(); odcI++)
	{
		Diag[l[odcI]] += Lower[odcI];
		Diag[u[odcI]] += Upper[odcI];
	}
}


void tnbLib::lduMatrix::negSumDiag()
{
	const scalarField& Lower = const_cast<const lduMatrix&>(*this).lower();
	const scalarField& Upper = const_cast<const lduMatrix&>(*this).upper();
	scalarField& Diag = diag();

	const unallocLabelList& l = lduAddr().lowerAddr();
	const unallocLabelList& u = lduAddr().upperAddr();

	for (register label odcI = 0; odcI < l.size(); odcI++)
	{
		Diag[l[odcI]] -= Lower[odcI];
		Diag[u[odcI]] -= Upper[odcI];
	}
}


void tnbLib::lduMatrix::sumMagOffDiag
(
	scalarField& sumOff
) const
{
	const scalarField& Lower = const_cast<const lduMatrix&>(*this).lower();
	const scalarField& Upper = const_cast<const lduMatrix&>(*this).upper();

	const unallocLabelList& l = lduAddr().lowerAddr();
	const unallocLabelList& u = lduAddr().upperAddr();

	for (register label odcI = 0; odcI < l.size(); odcI++)
	{
		sumOff[u[odcI]] += mag(Lower[odcI]);
		sumOff[l[odcI]] += mag(Upper[odcI]);
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::lduMatrix::operator=(const lduMatrix& A)
{
	if (this == &A)
	{
		FatalError
			<< "lduMatrix::operator=(const lduMatrix&) : "
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	if (A.lowerPtr_)
	{
		lower() = A.lower();
	}
	else if (lowerPtr_)
	{
		delete lowerPtr_;
		lowerPtr_ = NULL;
	}

	if (A.upperPtr_)
	{
		upper() = A.upper();
	}
	else if (upperPtr_)
	{
		delete upperPtr_;
		upperPtr_ = NULL;
	}

	if (A.diagPtr_)
	{
		diag() = A.diag();
	}
}


void tnbLib::lduMatrix::negate()
{
	if (lowerPtr_)
	{
		lowerPtr_->negate();
	}

	if (upperPtr_)
	{
		upperPtr_->negate();
	}

	if (diagPtr_)
	{
		diagPtr_->negate();
	}
}


void tnbLib::lduMatrix::operator+=(const lduMatrix& A)
{
	if (A.diagPtr_)
	{
		diag() += A.diag();
	}

	if (symmetric() && A.symmetric())
	{
		upper() += A.upper();
	}
	else if (symmetric() && A.asymmetric())
	{
		if (upperPtr_)
		{
			lower();
		}
		else
		{
			upper();
		}

		upper() += A.upper();
		lower() += A.lower();
	}
	else if (asymmetric() && A.symmetric())
	{
		if (A.upperPtr_)
		{
			lower() += A.upper();
			upper() += A.upper();
		}
		else
		{
			lower() += A.lower();
			upper() += A.lower();
		}

	}
	else if (asymmetric() && A.asymmetric())
	{
		lower() += A.lower();
		upper() += A.upper();
	}
	else if (diagonal())
	{
		if (A.upperPtr_)
		{
			upper() = A.upper();
		}

		if (A.lowerPtr_)
		{
			lower() = A.lower();
		}
	}
	else if (A.diagonal())
	{
	}
	else
	{
		FatalErrorIn("lduMatrix::operator+=(const lduMatrix& A)")
			<< "Unknown matrix type combination"
			<< abort(FatalError);
	}
}


void tnbLib::lduMatrix::operator-=(const lduMatrix& A)
{
	if (A.diagPtr_)
	{
		diag() -= A.diag();
	}

	if (symmetric() && A.symmetric())
	{
		upper() -= A.upper();
	}
	else if (symmetric() && A.asymmetric())
	{
		if (upperPtr_)
		{
			lower();
		}
		else
		{
			upper();
		}

		upper() -= A.upper();
		lower() -= A.lower();
	}
	else if (asymmetric() && A.symmetric())
	{
		if (A.upperPtr_)
		{
			lower() -= A.upper();
			upper() -= A.upper();
		}
		else
		{
			lower() -= A.lower();
			upper() -= A.lower();
		}

	}
	else if (asymmetric() && A.asymmetric())
	{
		lower() -= A.lower();
		upper() -= A.upper();
	}
	else if (diagonal())
	{
		if (A.upperPtr_)
		{
			upper() = -A.upper();
		}

		if (A.lowerPtr_)
		{
			lower() = -A.lower();
		}
	}
	else if (A.diagonal())
	{
	}
	else
	{
		FatalErrorIn("lduMatrix::operator-=(const lduMatrix& A)")
			<< "Unknown matrix type combination"
			<< abort(FatalError);
	}
}


void tnbLib::lduMatrix::operator*=(const scalarField& sf)
{
	if (diagPtr_)
	{
		*diagPtr_ *= sf;
	}

	if (upperPtr_)
	{
		scalarField& upper = *upperPtr_;

		const unallocLabelList& l = lduAddr().lowerAddr();

		for (register label odcI = 0; odcI < upper.size(); odcI++)
		{
			upper[odcI] *= sf[l[odcI]];
		}
	}

	if (lowerPtr_)
	{
		scalarField& lower = *lowerPtr_;

		const unallocLabelList& u = lduAddr().upperAddr();

		for (register label odcI = 0; odcI < lower.size(); odcI++)
		{
			lower[odcI] *= sf[u[odcI]];
		}
	}
}


void tnbLib::lduMatrix::operator*=(scalar s)
{
	if (diagPtr_)
	{
		*diagPtr_ *= s;
	}

	if (upperPtr_)
	{
		*upperPtr_ *= s;
	}

	if (lowerPtr_)
	{
		*lowerPtr_ *= s;
	}
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::lduMatrix::H1() const
{
	tmp<scalarField > tH1
	(
		new scalarField(lduAddr().size(), 0.0)
	);

	if (lowerPtr_ || upperPtr_)
	{
		scalarField& H1_ = tH1();

		scalar* __restrict H1Ptr = H1_.begin();

		const label* __restrict uPtr = lduAddr().upperAddr().begin();
		const label* __restrict lPtr = lduAddr().lowerAddr().begin();

		const scalar* __restrict lowerPtr = lower().begin();
		const scalar* __restrict upperPtr = upper().begin();

		register const label nOdcIs = upper().size();

		for (register label odcI = 0; odcI < nOdcIs; odcI++)
		{
			H1Ptr[uPtr[odcI]] -= lowerPtr[odcI];
			H1Ptr[lPtr[odcI]] -= upperPtr[odcI];
		}
	}

	return tH1;
}


// ************************************************************************* //