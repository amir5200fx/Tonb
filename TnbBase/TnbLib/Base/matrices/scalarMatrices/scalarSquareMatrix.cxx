#include <scalarSquareMatrix.hxx>

#include <vector>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::scalarSquareMatrix::scalarSquareMatrix()
{}


tnbLib::scalarSquareMatrix::scalarSquareMatrix(const label mSize)
	:
	SquareMatrix<scalar>(mSize, 0.0)
{}


tnbLib::scalarSquareMatrix::scalarSquareMatrix
(
	const label mSize,
	const scalar v
)
	: SquareMatrix<scalar>(mSize, v)
{}


tnbLib::scalarSquareMatrix::scalarSquareMatrix(const scalarSquareMatrix& matrix)
	:
	SquareMatrix<scalar>(matrix)
{}


tnbLib::scalarSquareMatrix::scalarSquareMatrix(Istream& is)
	: SquareMatrix<scalar>(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::scalarSquareMatrix::LUDecompose
(
	scalarSquareMatrix& matrix,
	labelList& pivotIndices
)
{
	label n = matrix.n();
	//scalar vv[n];
	std::vector<scalar> vv(n);

	for (register label i = 0; i < n; i++)
	{
		scalar largestCoeff = 0.0;
		scalar temp;
		const scalar* __restrict matrixi = matrix[i];

		for (register label j = 0; j < n; j++)
		{
			if ((temp = mag(matrixi[j])) > largestCoeff)
			{
				largestCoeff = temp;
			}
		}

		if (largestCoeff == 0.0)
		{
			FatalErrorIn
			(
				"scalarSquareMatrix::LUdecompose"
				"(scalarSquareMatrix& matrix, labelList& rowIndices)"
			) << "Singular matrix" << exit(FatalError);
		}

		vv[i] = 1.0 / largestCoeff;
	}

	for (register label j = 0; j < n; j++)
	{
		scalar* __restrict matrixj = matrix[j];

		for (register label i = 0; i < j; i++)
		{
			scalar* __restrict matrixi = matrix[i];

			scalar sum = matrixi[j];
			for (register label k = 0; k < i; k++)
			{
				sum -= matrixi[k] * matrix[k][j];
			}
			matrixi[j] = sum;
		}

		label iMax = 0;

		scalar largestCoeff = 0.0;
		for (register label i = j; i < n; i++)
		{
			scalar* __restrict matrixi = matrix[i];
			scalar sum = matrixi[j];

			for (register label k = 0; k < j; k++)
			{
				sum -= matrixi[k] * matrix[k][j];
			}

			matrixi[j] = sum;

			scalar temp;
			if ((temp = vv[i] * mag(sum)) >= largestCoeff)
			{
				largestCoeff = temp;
				iMax = i;
			}
		}

		pivotIndices[j] = iMax;

		if (j != iMax)
		{
			scalar* __restrict matrixiMax = matrix[iMax];

			for (register label k = 0; k < n; k++)
			{
				Swap(matrixj[k], matrixiMax[k]);
			}

			vv[iMax] = vv[j];
		}

		if (matrixj[j] == 0.0)
		{
			matrixj[j] = SMALL;
		}

		if (j != n - 1)
		{
			scalar rDiag = 1.0 / matrixj[j];

			for (register label i = j + 1; i < n; i++)
			{
				matrix[i][j] *= rDiag;
			}
		}
	}
}


tnbLib::scalarSquareMatrix tnbLib::scalarSquareMatrix::LUinvert() const
{
	scalarSquareMatrix luMatrix = *this;

	scalarSquareMatrix luInvert(luMatrix.n());
	scalarField column(luMatrix.n());

	labelList pivotIndices(luMatrix.n());

	LUDecompose(luMatrix, pivotIndices);

	for (label j = 0; j < luMatrix.n(); j++)
	{
		for (label i = 0; i < luMatrix.n(); i++)
		{
			column[i] = 0.0;
		}

		column[j] = 1.0;

		LUBacksubstitute(luMatrix, pivotIndices, column);

		for (label i = 0; i < luMatrix.n(); i++)
		{
			luInvert[i][j] = column[i];
		}
	}

	return luInvert;
}


// ************************************************************************* //