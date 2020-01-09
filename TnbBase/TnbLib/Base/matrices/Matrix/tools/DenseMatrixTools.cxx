#include <DenseMatrixTools.hxx>

#include <Swap.hxx>
#include <labelList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Solve with pivoting.  Note: Destroys matrix and b
template<class T>
static void tnbLib::DenseMatrixTools::solve
(
	SquareMatrix<T>& A,
	List<T>& x,
	List<T>& b
)
{
	const label nRows = A.n();

	// Create and initialise permutation array
	labelList p(nRows);

	forAll(p, i)
	{
		p[i] = i;
	}


	// Eliminate equations
	for (label k = 0; k < nRows - 1; k++)
	{
		// Swap rows
		label m = k;

		for (label i = k + 1; i < nRows; ++i)
		{
			if (tnbLib::mag(A[p[i]][k]) > tnbLib::mag(A[p[m]][k]))
			{
				m = i;
			}

			Swap(p[k], p[m]);
		}


		for (label i = k + 1; i < nRows; i++)
		{
			label pi = p[i];
			label pk = p[k];

			//             T r = A[pi][k]/A[pk][k];
			T r = cmptDivide(A[pi][k], A[pk][k]);

			for (label j = k + 1; j < nRows; j++)
			{
				//                 A[pi][j] -= A[pk][j]*r;
				A[pi][j] -= cmptMultiply(A[pk][j], r);
			}

			//             b[pi] -= b[pk]*r;
			b[pi] -= cmptMultiply(b[pk], r);
		}
	}

	// Back substitute
	for (label i = nRows - 1; i >= 0; i--)
	{
		label pi = p[i];

		T sum = b[pi];

		for (label j = i + 1; j < nRows; j++)
		{
			//             sum -= A[pi][j]*x[j];
			sum -= cmptMultiply(A[pi][j], x[j]);
		}

		//         x[i] = sum/A[pi][i];
		x[i] = cmptDivide(sum, A[pi][i]);
	}
}


template<class Form, class Type>
static void tnbLib::DenseMatrixTools::qrDecompose
(
	const label nCols,
	FieldField<Field, Type>& A,
	Matrix<Form, Type>& R
)
{
	// Note: consider Arnoldi algorithm for speed-up.  HJ, 14/Sep/2006

	for (label j = 0; j < nCols; j++)
	{
		R[j][j] = tnbLib::sqrt(gSumSqr(A[j]));

		if (mag(R[j][j]) > SMALL)
		{
			A[j] /= R[j][j];
		}

		for (label k = j + 1; k < nCols; k++)
		{
			const Field<Type>& Aj = A[j];
			Field<Type>& Ak = A[k];
			Type& Rjk = R[j][k];

			Rjk = gSumProd(Aj, Ak);

			for (label i = 0; i < Ak.size(); i++)
			{
				Ak[i] -= Rjk * Aj[i];
			}
		}
	}
}


// ************************************************************************* //