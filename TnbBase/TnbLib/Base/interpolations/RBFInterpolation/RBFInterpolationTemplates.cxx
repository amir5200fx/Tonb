#include <RBFInterpolation.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::RBFInterpolation::interpolate
(
	const Field<Type>& ctrlField
) const
{
	// HJ and FB (05 Jan 2009)
	// Collect the values from ALL control points to all CPUs
	// Then, each CPU will do interpolation only on local dataPoints_

	if (ctrlField.size() != controlPoints_.size())
	{
		FatalErrorIn
		(
			"tmp<Field<Type> > RBFInterpolation::interpolate\n"
			"(\n"
			"    const Field<Type>& ctrlField\n"
			") const"
		) << "Incorrect size of source field.  Size = " << ctrlField.size()
			<< " nControlPoints = " << controlPoints_.size()
			<< abort(FatalError);
	}

	tmp<Field<Type> > tresult
	(
		new Field<Type>(dataPoints_.size(), pTraits<Type>::zero)
	);

	Field<Type>& result = tresult();

	// FB 21-12-2008
	// 1) Calculate alpha and beta coefficients using the Inverse
	// 2) Calculate displacements of internal nodes using RBF values,
	//    alpha's and beta's
	// 3) Return displacements using tresult()

	const label nControlPoints = controlPoints_.size();
	const scalarSquareMatrix& mat = this->B();

	// Determine interpolation coefficients
	Field<Type> alpha(nControlPoints, pTraits<Type>::zero);
	Field<Type> beta(4, pTraits<Type>::zero);

	for (label row = 0; row < nControlPoints; row++)
	{
		for (label col = 0; col < nControlPoints; col++)
		{
			alpha[row] += mat[row][col] * ctrlField[col];
		}
	}

	if (polynomials_)
	{
		for
			(
				label row = nControlPoints;
				row < nControlPoints + 4;
				row++
				)
		{
			for (label col = 0; col < nControlPoints; col++)
			{
				beta[row - nControlPoints] += mat[row][col] * ctrlField[col];
			}
		}
	}

	// Evaluation
	scalar t;

	// Algorithmic improvement, Matteo Lombardi.  21/Mar/2011

	forAll(dataPoints_, flPoint)
	{
		// Cut-off function to justify neglecting outer boundary points
		t = (mag(dataPoints_[flPoint] - focalPoint_) - innerRadius_) /
			(outerRadius_ - innerRadius_);

		if (t >= 1)
		{
			// Increment is zero: w = 0
			result[flPoint] = 0 * result[flPoint];
		}
		else
		{
			// Full calculation of weights
			scalarField weights =
				RBF_->weights(controlPoints_, dataPoints_[flPoint]);

			forAll(controlPoints_, i)
			{
				result[flPoint] += weights[i] * alpha[i];
			}

			if (polynomials_)
			{
				result[flPoint] +=
					beta[0]
					+ beta[1] * dataPoints_[flPoint].x()
					+ beta[2] * dataPoints_[flPoint].y()
					+ beta[3] * dataPoints_[flPoint].z();
			}

			scalar w;

			if (t <= 0)
			{
				w = 1.0;
			}
			else
			{
				w = 1 - sqr(t)*(3 - 2 * t);
			}

			result[flPoint] = w * result[flPoint];
		}
	}

	return tresult;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //