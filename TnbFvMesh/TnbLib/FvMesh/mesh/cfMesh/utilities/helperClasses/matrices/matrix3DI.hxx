#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline void matrix3D::calculateDeterminant()
	{
		if (calculatedDet_)
			return;

		const FixedList<FixedList<scalar, 3>, 3>& mat = *this;

		det_ =
			mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
			mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
			mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);

		calculatedDet_ = true;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline matrix3D::matrix3D()
		:
		det_(),
		calculatedDet_(false)
	{}

	inline matrix3D::matrix3D(const matrix3D& m)
		:
		FixedList<FixedList<scalar, 3>, 3>(m),
		det_(m.det_),
		calculatedDet_(m.calculatedDet_)
	{}

	inline matrix3D::~matrix3D()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline scalar matrix3D::determinant()
	{
		calculateDeterminant();

		return det_;
	}

	inline matrix3D matrix3D::inverse()
	{
		calculateDeterminant();

		const FixedList<FixedList<scalar, 3>, 3>& mat = *this;

		matrix3D imat;
		imat[0][0] = (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) / det_;
		imat[0][1] = (mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2]) / det_;
		imat[0][2] = (mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1]) / det_;
		imat[1][0] = (mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2]) / det_;
		imat[1][1] = (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]) / det_;
		imat[1][2] = (mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2]) / det_;
		imat[2][0] = (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]) / det_;
		imat[2][1] = (mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1]) / det_;
		imat[2][2] = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) / det_;

		return imat;
	}

	inline FixedList<scalar, 3> matrix3D::solve
	(
		const FixedList<scalar, 3>& source
	)
	{
		FixedList<scalar, 3> result;
		result[0] = solveFirst(source);
		result[1] = solveSecond(source);
		result[2] = solveThird(source);

		return result;
	}

	inline scalar matrix3D::solveFirst(const FixedList<scalar, 3>& source)
	{
		calculateDeterminant();

		const FixedList<FixedList<scalar, 3>, 3>& mat = *this;

		return
			(
			(mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) * source[0] +
				(mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2]) * source[1] +
				(mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1]) * source[2]
				) / det_;
	}

	inline scalar matrix3D::solveSecond(const FixedList<scalar, 3>& source)
	{
		calculateDeterminant();

		const FixedList<FixedList<scalar, 3>, 3>& mat = *this;

		return
			(
			(mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2]) * source[0] +
				(mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]) * source[1] +
				(mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2]) * source[2]
				) / det_;
	}

	inline scalar matrix3D::solveThird(const FixedList<scalar, 3>& source)
	{
		calculateDeterminant();

		const FixedList<FixedList<scalar, 3>, 3>& mat = *this;

		return
			(
			(mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]) * source[0] +
				(mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1]) * source[1] +
				(mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) * source[2]
				) / det_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //