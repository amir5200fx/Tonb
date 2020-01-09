#include <GGIBlockAMGInterfaceField.hxx>

#include <ggiLduInterfaceField.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <blockLduMatrices.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
template<class Type2>
void tnbLib::GGIBlockAMGInterfaceField<Type>::agglomerateBlockType
(
	Field<Type2>& coarseCoeffs,
	const tnbLib::Field<Type2>& fineCoeffs
) const
{
	// Note: reconsider better parallel communication here.
	// Currently expanding to full zone size
	// HJ, 16/Mar/2016

	// Get fine interface
	const ggiLduInterface& fineGgiInterface = ggiInterface_.fineGgiInterface();

	// Reassemble fine coefficients to full fine zone size
	// No need to initialise to zero, as only local coefficients
	// are used.  HJ, 9/Jun/2016
	Field<Type2> zoneFineCoeffs(fineGgiInterface.zoneSize());

	const labelList& fineZa = fineGgiInterface.zoneAddressing();

	forAll(fineZa, i)
	{
		zoneFineCoeffs[fineZa[i]] = fineCoeffs[i];
	}

	// Reduce zone data is not required: all coefficients are local
	// HJ, 9/Jun/2016

	Field<Type2> zoneCoarseCoeffs
	(
		ggiInterface_.zoneSize(),
		pTraits<Type2>::zero
	);

	// Get addressing from the fine interface
	const labelField& fineAddressing = ggiInterface_.fineAddressing();
	const labelField& restrictAddressing = ggiInterface_.restrictAddressing();
	const scalarField& restrictWeights = ggiInterface_.restrictWeights();

	// Restrict coefficients
	forAll(restrictAddressing, ffi)
	{
		zoneCoarseCoeffs[restrictAddressing[ffi]] +=
			restrictWeights[ffi] * zoneFineCoeffs[fineAddressing[ffi]];
	}

	// Filter zone coefficients to local field
	const labelList& za = ggiInterface_.zoneAddressing();

	forAll(za, i)
	{
		coarseCoeffs[i] = zoneCoarseCoeffs[za[i]];
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::GGIBlockAMGInterfaceField<Type>::GGIBlockAMGInterfaceField
(
	const AMGInterface& AMGCp,
	const BlockLduInterfaceField<Type>& fineInterfaceField
)
	:
	BlockAMGInterfaceField<Type>(AMGCp, fineInterfaceField),
	ggiInterface_(refCast<const ggiAMGInterface>(AMGCp)),
	doTransform_(false),
	rank_(),
	fieldTransferBuffer_()
{
	// If the interface based on a patch this must be taken care specially of
	if (isA<GGIBlockLduInterfaceField<Type> >(fineInterfaceField))
	{
		const GGIBlockLduInterfaceField<Type>& p =
			refCast<const GGIBlockLduInterfaceField<Type> >
			(
				fineInterfaceField
				);

		doTransform_ = p.doTransform();
		rank_ = p.rank();
	}
	else if (isA<ggiLduInterfaceField>(fineInterfaceField))
	{
		const ggiLduInterfaceField& p =
			refCast<const ggiLduInterfaceField >(fineInterfaceField);

		doTransform_ = p.doTransform();
		rank_ = p.rank();
	}
	else
	{
		FatalErrorIn("GGIBlockAMGInterfaceField<Type> Constructor")
			<< "fineInterface must be of ggi type and either" << endl
			<< "    GGIBlockLduInterfaceField<Type> or " << endl
			<< "    ggiFvPatchField<Type> " << endl
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::GGIBlockAMGInterfaceField<Type>::~GGIBlockAMGInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::CoeffField<Type> >
tnbLib::GGIBlockAMGInterfaceField<Type>::agglomerateBlockCoeffs
(
	const tnbLib::CoeffField<Type>& fineCoeffs
) const
{
	tmp<CoeffField<Type> > tcoarseCoeffs(new CoeffField<Type>(size()));
	CoeffField<Type>& coarseCoeffs = tcoarseCoeffs();

	typedef CoeffField<Type> TypeCoeffField;

	typedef typename TypeCoeffField::linearTypeField linearTypeField;
	typedef typename TypeCoeffField::squareTypeField squareTypeField;

	// Added weights to account for non-integral matching
	if (fineCoeffs.activeType() == blockCoeffBase::SQUARE)
	{
		squareTypeField& activeCoarseCoeffs = coarseCoeffs.asSquare();
		const squareTypeField& activeFineCoeffs = fineCoeffs.asSquare();

		this->agglomerateBlockType(activeCoarseCoeffs, activeFineCoeffs);
	}
	else if (fineCoeffs.activeType() == blockCoeffBase::LINEAR)
	{
		linearTypeField& activeCoarseCoeffs = coarseCoeffs.asLinear();
		const linearTypeField& activeFineCoeffs = fineCoeffs.asLinear();

		this->agglomerateBlockType(activeCoarseCoeffs, activeFineCoeffs);
	}
	else
	{
		FatalErrorIn
		(
			"tnbLib::tmp<tnbLib::CoeffField<Type> >\n"
			"tnbLib::GGIBlockAMGInterfaceField<Type>::agglomerateBlockCoeffs\n"
			"(\n"
			"    const tnbLib::CoeffField<Type>& fineCoeffs\n"
			") const"
		) << "Scalar type agglomeration currently not handled"
			<< abort(FatalError);
	}

	return tcoarseCoeffs;
}


template<class Type>
void tnbLib::GGIBlockAMGInterfaceField<Type>::initInterfaceMatrixUpdate
(
	const Field<Type>& psiInternal,
	Field<Type>&,
	const BlockLduMatrix<Type>&,
	const CoeffField<Type>&,
	const Pstream::commsTypes,
	const bool switchToLhs
) const
{
	// This must have a reduce in it.  HJ, 15/May/2009
	Field<Type> pif = ggiInterface_.interfaceInternalField(psiInternal);

	fieldTransferBuffer_ = ggiInterface_.fastReduce(pif);
}


template<class Type>
void tnbLib::GGIBlockAMGInterfaceField<Type>::updateInterfaceMatrix
(
	const Field<Type>& psiInternal,
	Field<Type>& result,
	const BlockLduMatrix<Type>& matrix,
	const CoeffField<Type>& coeffs,
	const Pstream::commsTypes commsType,
	const bool switchToLhs
) const
{
	// Get interface from shadow
	const GGIBlockAMGInterfaceField<Type>& shadowInterface =
		refCast<const GGIBlockAMGInterfaceField<Type> >
		(
			matrix.interfaces()[ggiInterface_.shadowIndex()]
			);

	Field<Type> pnf = shadowInterface.fieldTransferBuffer();

	// Complex (VectorN) transformation happens here.
	// HJ, 17/Feb/2016
//     transformCoupleField(pnf, cmpt);

	// Multiply neighbour field with coeffs and re-use pnf for result
	// of multiplication
	multiply(pnf, coeffs, pnf);

	const unallocLabelList& faceCells = ggiInterface_.faceCells();

	if (switchToLhs)
	{
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] += pnf[elemI];
		}
	}
	else
	{
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] -= pnf[elemI];
		}
	}
}


// ************************************************************************* //