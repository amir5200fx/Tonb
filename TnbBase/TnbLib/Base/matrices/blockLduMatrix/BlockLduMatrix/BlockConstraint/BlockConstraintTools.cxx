#include <BlockConstraint.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void BlockConstraint<Type>::setMatrix
	(
		const BlockLduMatrix<Type>& matrix,
		const TypeField& x,
		const TypeField& b
	)
	{
		if (matrixCoeffsSet_)
		{
			FatalErrorIn
			(
				"void BlockConstraint<Type>::setMatrix\n"
				"(\n"
				"    const BlockLduMatrix<Type>& matrix,\n"
				"    const TypeField& x,\n"
				"    const TypeField& b\n"
				")"
			) << "matrix coefficients already set"
				<< abort(FatalError);
		}

		matrixCoeffsSet_ = true;

		if (matrix.thereIsDiag())
		{
			diagCoeff_ = matrix.diag().getCoeff(rowID_);
		}

		b_ = b[rowID_];

		const label startFaceOwn =
			matrix.lduAddr().ownerStartAddr()[rowID_];
		const label endFaceOwn =
			matrix.lduAddr().ownerStartAddr()[rowID_ + 1];
		const label ownSize = endFaceOwn - startFaceOwn;

		const label startFaceNbr =
			matrix.lduAddr().losortStartAddr()[rowID_];
		const label endFaceNbr =
			matrix.lduAddr().losortStartAddr()[rowID_ + 1];
		const label nbrSize = endFaceNbr - startFaceNbr;

		const unallocLabelList& losort = matrix.lduAddr().losortAddr();

		// Create losort addressing
		labelList losortAddr(nbrSize);

		forAll(losortAddr, laI)
		{
			losortAddr[laI] = losort[startFaceNbr + laI];
		}

		if (matrix.thereIsUpper())
		{
			// Get the upper coefficients

			const TypeCoeffField& matrixUpper = matrix.upper();

			// owner side
			upperCoeffsOwnerPtr_ = new TypeCoeffField(ownSize);
			TypeCoeffField& uOwn = *upperCoeffsOwnerPtr_;

			matrixUpper.getSubset(uOwn, startFaceOwn, ownSize);

			// neighbour side
			upperCoeffsNeighbourPtr_ = new TypeCoeffField(nbrSize);
			TypeCoeffField& uNbr = *upperCoeffsNeighbourPtr_;

			matrixUpper.getSubset(uNbr, losortAddr);
		}

		if (matrix.thereIsLower())
		{
			// Get the lower coefficients

			const TypeCoeffField& matrixLower = matrix.lower();

			// owner side
			lowerCoeffsOwnerPtr_ = new TypeCoeffField(ownSize);
			TypeCoeffField& lOwn = *lowerCoeffsOwnerPtr_;

			matrixLower.getSubset(lOwn, startFaceOwn, ownSize);

			// neighbour side
			lowerCoeffsNeighbourPtr_ = new TypeCoeffField(nbrSize);
			TypeCoeffField& lNbr = *lowerCoeffsNeighbourPtr_;

			matrixLower.getSubset(lNbr, losortAddr);
		}
	}


	template<class Type>
	void BlockConstraint<Type>::eliminateEquation
	(
		BlockLduMatrix<Type>& matrix,
		TypeField& b
	) const
	{
		const label startFaceOwn =
			matrix.lduAddr().ownerStartAddr()[rowID_];
		const label endFaceOwn =
			matrix.lduAddr().ownerStartAddr()[rowID_ + 1];
		const label ownSize = endFaceOwn - startFaceOwn;

		const label startFaceNbr =
			matrix.lduAddr().losortStartAddr()[rowID_];
		const label endFaceNbr =
			matrix.lduAddr().losortStartAddr()[rowID_ + 1];
		const label nbrSize = endFaceNbr - startFaceNbr;

		const unallocLabelList& owner = matrix.lduAddr().lowerAddr();
		const unallocLabelList& neighbour = matrix.lduAddr().upperAddr();
		const unallocLabelList& losort = matrix.lduAddr().losortAddr();

		// Create losort addressing
		labelList losortAddr(nbrSize);

		forAll(losortAddr, laI)
		{
			losortAddr[laI] = losort[startFaceNbr + laI];
		}

		typename BlockCoeff<Type>::multiply mult;

		// My index = rowID_
		if (matrix.symmetric())
		{
			TypeField bOwn;
			TypeField bNbr;

			TypeCoeffField& upperLower = matrix.upper();
			upperLower.zeroOutSubset(startFaceOwn, ownSize);
			upperLower.zeroOutSubset(losortAddr);

			bOwn = upperCoeffsOwner()*value_;
			bNbr = upperCoeffsNeighbour()*value_;

			// owner side

			forAll(bOwn, soI)
			{
				// add contribution to b of the neighbour (I am the owner)
				b[neighbour[startFaceOwn + soI]] -= bOwn[soI];
			}

			// neighbour side

			forAll(bNbr, snI)
			{
				// add contribution to b of owner (I am the neighbour)
				b[owner[losort[startFaceNbr + snI]]] -= bNbr[snI];
			}
		}
		else if (matrix.asymmetric())
		{
			// Do upper
			TypeCoeffField& matrixUpper = matrix.upper();

			matrixUpper.zeroOutSubset(startFaceOwn, ownSize);
			TypeField bOwn = lowerCoeffsOwner()*value_;

			// Do lower
			TypeCoeffField& matrixLower = matrix.lower();

			matrixLower.zeroOutSubset(losortAddr);
			TypeField bNbr = upperCoeffsNeighbour()*value_;

			// owner side

			forAll(bOwn, soI)
			{
				// add contribution to b of the neighbour (I am the owner)
				b[neighbour[startFaceOwn + soI]] -= bOwn[soI];
			}

			// neighbour side

			forAll(bNbr, snI)
			{
				// add contribution to b of owner (I am the neighbour)
				b[owner[losort[startFaceNbr + snI]]] -= bNbr[snI];
			}
		}
	}


	template<class Type>
	void BlockConstraint<Type>::setSourceDiag
	(
		BlockLduMatrix<Type>& matrix,
		Field<Type>& x,
		Field<Type>& b
	) const
	{
		const Type& fc = fixedComponents();

		typename BlockCoeff<Type>::multiply mult;

		if (mag(fc) > SMALL)
		{
			b[rowID()] =
				cmptMultiply
				(
					fc,
					mult(matrix.diag().getCoeff(rowID()), value())
				);

			// set the solution to the right value as well
			x[rowID()] = cmptMultiply(fc, value());
		}
	}


	template<class Type>
	void BlockConstraint<Type>::reconstructMatrix
	(
		BlockLduMatrix<Type>& matrix
	) const
	{
		if (!matrixCoeffsSet_)
		{
			FatalErrorIn
			(
				"void BlockConstraint<Type>::reconstructMatrix("
				"BlockLduMatrix<Type>& matrix)"
			) << "matrix coefficients not set"
				<< abort(FatalError);
		}

		if (matrix.thereIsDiag())
		{
			matrix.diag().setCoeff(rowID_, diagCoeff_);
		}

		const label startFaceOwn =
			matrix.lduAddr().ownerStartAddr()[rowID_];
		const label endFaceOwn =
			matrix.lduAddr().ownerStartAddr()[rowID_ + 1];
		const label ownSize = endFaceOwn - startFaceOwn;

		const label startFaceNbr =
			matrix.lduAddr().losortStartAddr()[rowID_];
		const label endFaceNbr =
			matrix.lduAddr().losortStartAddr()[rowID_ + 1];
		const label nbrSize = endFaceNbr - startFaceNbr;

		const unallocLabelList& losort = matrix.lduAddr().losortAddr();

		// Create losort addressing
		labelList losortAddr(nbrSize);

		forAll(losortAddr, laI)
		{
			losortAddr[laI] = losort[startFaceNbr + laI];
		}

		if (matrix.thereIsUpper())
		{
			// Get the upper coefficients

			TypeCoeffField& matrixUpper = matrix.upper();

			// owner side
			const TypeCoeffField& uOwn = upperCoeffsOwner();

			matrixUpper.setSubset(uOwn, startFaceOwn, ownSize);

			// neighbour side
			const TypeCoeffField& uNbr = upperCoeffsNeighbour();

			matrixUpper.setSubset(uNbr, losortAddr);
		}

		if (matrix.thereIsLower())
		{
			// Get the lower coefficients

			TypeCoeffField& matrixLower = matrix.lower();

			// owner side
			const TypeCoeffField& lOwn = lowerCoeffsOwner();

			matrixLower.setSubset(lOwn, startFaceOwn, ownSize);

			// neighbour side
			const TypeCoeffField& lNbr = lowerCoeffsNeighbour();

			matrixLower.setSubset(lNbr, losortAddr);
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //