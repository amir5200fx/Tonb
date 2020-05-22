#pragma once
#ifndef _processorFvPatchScalarField_Header
#define _processorFvPatchScalarField_Header

#include <processorFvPatchField.hxx>
#include <scalarCoeffField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<>
	void processorFvPatchField<scalar>::initInterfaceMatrixUpdate
	(
		const scalarField&,
		scalarField&,
		const lduMatrix&,
		const scalarField&,
		const direction,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const;


	template<>
	void processorFvPatchField<scalar>::updateInterfaceMatrix
	(
		const scalarField&,
		scalarField& result,
		const lduMatrix&,
		const scalarField& coeffs,
		const direction,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const;


	template<>
	void processorFvPatchField<scalar>::initInterfaceMatrixUpdate
	(
		const scalarField& psiInternal,
		scalarField&,
		const BlockLduMatrix<scalar>&,
		const CoeffField<scalar>&,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const;


	template<>
	void processorFvPatchField<scalar>::updateInterfaceMatrix
	(
		const scalarField&,
		scalarField& result,
		const BlockLduMatrix<scalar>&,
		const CoeffField<scalar>& coeffs,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorFvPatchScalarField_Header
