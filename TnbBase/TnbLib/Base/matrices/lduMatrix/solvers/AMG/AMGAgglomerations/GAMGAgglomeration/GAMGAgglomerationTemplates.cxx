#include <GAMGAgglomeration.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::GAMGAgglomeration::restrictField
(
	Field<Type>& cf,
	const Field<Type>& ff,
	const label fineLevelIndex
) const
{
	const labelList& fineToCoarse = restrictAddressing_[fineLevelIndex];

	if (ff.size() != fineToCoarse.size())
	{
		FatalErrorIn
		(
			"void GAMGAgglomeration::restrictField"
			"(Field<Type>& cf, const Field<Type>& ff, "
			"const label fineLevelIndex) const"
		) << "field does not correspond to level " << fineLevelIndex
			<< " sizes: field = " << ff.size()
			<< " level = " << fineToCoarse.size()
			<< abort(FatalError);
	}

	cf = pTraits<Type>::zero;

	forAll(ff, i)
	{
		cf[fineToCoarse[i]] += ff[i];
	}
}


template<class Type>
void tnbLib::GAMGAgglomeration::restrictFaceField
(
	Field<Type>& cf,
	const Field<Type>& ff,
	const label fineLevelIndex
) const
{
	const labelList& fineToCoarse = faceRestrictAddressing_[fineLevelIndex];

	cf = pTraits<Type>::zero;

	forAll(fineToCoarse, ffacei)
	{
		label cFace = fineToCoarse[ffacei];

		if (cFace >= 0)
		{
			cf[cFace] += ff[ffacei];
		}
	}
}


template<class Type>
void tnbLib::GAMGAgglomeration::prolongField
(
	Field<Type>& ff,
	const Field<Type>& cf,
	const label coarseLevelIndex
) const
{
	const labelList& fineToCoarse = restrictAddressing_[coarseLevelIndex];

	forAll(fineToCoarse, i)
	{
		ff[i] = cf[fineToCoarse[i]];
	}
}


// ************************************************************************* //