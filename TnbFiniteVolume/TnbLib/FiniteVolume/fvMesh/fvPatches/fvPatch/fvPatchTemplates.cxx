#include <fvPatch.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::fvPatch::patchInternalField
(
	const UList<Type>& f
) const
{
	tmp<Field<Type> > tpif(new Field<Type>(size()));
	Field<Type>& pif = tpif();

	const unallocLabelList& faceCells = this->faceCells();

	forAll(pif, facei)
	{
		pif[facei] = f[faceCells[facei]];
	}

	return tpif;
}


template<class GeometricField, class Type>
const typename GeometricField::PatchFieldType& tnbLib::fvPatch::patchField
(
	const GeometricField& gf
) const
{
	return gf.boundaryField()[index()];
}


// ************************************************************************* //