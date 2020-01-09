#include <BlockDiagonalPrecon.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::BlockDiagonalPrecon<Type>::precondition
(
	Field<Type>& x,
	const Field<Type>& b
) const
{
	typedef CoeffField<Type> TypeCoeffField;

	typedef typename TypeCoeffField::scalarTypeField scalarTypeField;
	typedef typename TypeCoeffField::linearTypeField linearTypeField;
	typedef typename TypeCoeffField::squareTypeField squareTypeField;

	const TypeCoeffField& diag = this->matrix_.diag();

	if (diag.activeType() == blockCoeffBase::SCALAR)
	{
		const scalarTypeField& activeDiag = diag.asScalar();

		forAll(x, i)
		{
			x[i] = b[i] / activeDiag[i];
		}
	}
	else if (diag.activeType() == blockCoeffBase::LINEAR)
	{
		const linearTypeField& activeDiag = diag.asLinear();

		forAll(x, i)
		{
			x[i] = cmptDivide(b[i], activeDiag[i]);
		}
	}
	else if (diag.activeType() == blockCoeffBase::SQUARE)
	{
		const squareTypeField& activeDiag = diag.asSquare();

		forAll(x, i)
		{
			x[i] = (b[i] & inv(activeDiag[i]));
		}
	}
	else
	{
		FatalErrorIn
		(
			"void BlockDiagonalPrecon<Type>:solve:\n"
			"(\n"
			"    Field<Type>& x,\n"
			"    const Field<Type>& b\n"
			") const"
		) << "Problem with coefficient type morphing."
			<< abort(FatalError);
	}
}


// ************************************************************************* //