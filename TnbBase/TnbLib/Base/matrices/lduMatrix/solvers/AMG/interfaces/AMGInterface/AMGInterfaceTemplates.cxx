#include <AMGInterface.hxx>

#include <scalarCoeffField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::AMGInterface::interfaceInternalField
(
	const UList<Type>& iF
) const
{
	tmp<Field<Type> > tresult(new Field<Type>(size()));
	Field<Type>& result = tresult();

	forAll(result, elemI)
	{
		result[elemI] = iF[faceCells_[elemI]];
	}

	return tresult;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //