#include <tensorBlockDiagonalPrecon.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void tnbLib::BlockDiagonalPrecon<tensor>::precondition
	(
		tensorField& x,
		const tensorField& b
	) const
	{
		typedef CoeffField<tensor> tensorCoeffField;

		typedef tensorCoeffField::scalarTypeField scalarTypeField;
		typedef tensorCoeffField::linearTypeField linearTypeField;

		const tensorCoeffField& diag = matrix_.diag();

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
		else
		{
			FatalErrorIn
			(
				"void BlockDiagonalPrecon<tensor>::solve\n"
				"(\n"
				"    tensorField& x,\n"
				"    const tensorField& b\n"
				") const"
			) << "Problem with coefficient type morphing."
				<< abort(FatalError);
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //