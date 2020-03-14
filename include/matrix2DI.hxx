#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline void matrix2D::calculateDeterminant()
	{
		if (calculatedDet_)
			return;

		const FixedList<FixedList<scalar, 2>, 2>& mat = *this;
		det_ = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

		calculatedDet_ = true;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline matrix2D::matrix2D()
		:
		det_(),
		calculatedDet_(false)
	{}

	inline matrix2D::matrix2D(const matrix2D& m)
		:
		FixedList<FixedList<scalar, 2>, 2>(m),
		det_(m.det_),
		calculatedDet_(m.calculatedDet_)
	{}

	inline matrix2D::~matrix2D()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline scalar matrix2D::determinant()
	{
		calculateDeterminant();

		return det_;
	}

	inline matrix2D matrix2D::inverse()
	{
		calculateDeterminant();

		const FixedList<FixedList<scalar, 2>, 2>& mat = *this;

		matrix2D imat;
		imat[0][0] = mat[1][1] / det_;
		imat[0][1] = -1.0 * mat[0][1] / det_;
		imat[1][0] = -1.0 * mat[1][0] / det_;
		imat[1][1] = mat[0][0] / det_;

		return matrix2D(imat);
	}

	inline FixedList<scalar, 2> matrix2D::solve
	(
		const FixedList<scalar, 2>& source
	)
	{
		FixedList<scalar, 2> result;
		result[0] = solveFirst(source);
		result[1] = solveSecond(source);

		return result;
	}

	inline scalar matrix2D::solveFirst(const FixedList<scalar, 2>& source)
	{
		calculateDeterminant();

		const FixedList<FixedList<scalar, 2>, 2>& mat = *this;

		return
			(
				mat[1][1] * source[0] -
				mat[0][1] * source[1]
				) / det_;
	}

	inline scalar matrix2D::solveSecond(const FixedList<scalar, 2>& source)
	{
		calculateDeterminant();

		const FixedList<FixedList<scalar, 2>, 2>& mat = *this;

		return
			(
				-1.0 * mat[1][0] * source[0] +
				mat[0][0] * source[1]
				) / det_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //