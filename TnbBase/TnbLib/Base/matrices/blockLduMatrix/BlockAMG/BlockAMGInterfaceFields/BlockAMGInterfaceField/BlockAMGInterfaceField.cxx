#include <BlockAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::CoeffField<Type> >
tnbLib::BlockAMGInterfaceField<Type>::agglomerateBlockCoeffs
(
	const tnbLib::CoeffField<Type>& fineCoeffs
) const
{
	tmp<CoeffField<Type> > tcoarseCoeffs
	(
		new CoeffField<Type>(interface_.size())
	);
	CoeffField<Type>& coarseCoeffs = tcoarseCoeffs();

	typedef CoeffField<Type> TypeCoeffField;

	typedef typename TypeCoeffField::linearTypeField linearTypeField;
	typedef typename TypeCoeffField::squareTypeField squareTypeField;

	// Get addressing from the fine interface
	const labelField& fineAddressing = interface_.fineAddressing();
	const labelField& restrictAddressing = interface_.restrictAddressing();
	const scalarField& restrictWeights = interface_.restrictWeights();

	// Added weights to account for non-integral matching
	if (fineCoeffs.activeType() == blockCoeffBase::SQUARE)
	{
		squareTypeField& activeCoarseCoeffs = coarseCoeffs.asSquare();
		const squareTypeField& activeFineCoeffs = fineCoeffs.asSquare();

		activeCoarseCoeffs *= 0.0;

		// Added weights to account for non-integral matching
		forAll(restrictAddressing, ffi)
		{
			activeCoarseCoeffs[restrictAddressing[ffi]] +=
				restrictWeights[ffi] * activeFineCoeffs[fineAddressing[ffi]];
		}
	}
	else if (fineCoeffs.activeType() == blockCoeffBase::LINEAR)
	{
		linearTypeField& activeCoarseCoeffs = coarseCoeffs.asLinear();
		const linearTypeField& activeFineCoeffs = fineCoeffs.asLinear();

		activeCoarseCoeffs *= 0.0;

		// Added weights to account for non-integral matching
		forAll(restrictAddressing, ffi)
		{
			activeCoarseCoeffs[restrictAddressing[ffi]] +=
				restrictWeights[ffi] * activeFineCoeffs[fineAddressing[ffi]];
		}
	}
	else
	{
		FatalErrorIn
		(
			"tnbLib::tmp<tnbLib::CoeffField<Type> >\n"
			"tnbLib::BlockAMGInterfaceField<Type>::agglomerateBlockCoeffs\n"
			"(\n"
			"    const tnbLib::CoeffField<Type>& fineCoeffs\n"
			") const"
		) << "Scalar type agglomeration currently not handled"
			<< abort(FatalError);
	}

	return tcoarseCoeffs;
}


// ************************************************************************* //