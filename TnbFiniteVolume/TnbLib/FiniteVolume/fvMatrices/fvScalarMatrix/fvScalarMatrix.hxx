#pragma once
#ifndef _fvScalarMatrix_Header
#define _fvScalarMatrix_Header

#include <scalar.hxx>
#include <fvMatrix.hxx>
#include <scalarField.hxx>
#include <scalarFieldField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Set reference level for a component of the solution
	// on a given patch face

	template<>
	void fvMatrix<scalar>::setComponentReference
	(
		const label patchi,
		const label facei,
		const direction cmpt,
		const scalar value
	);

	template<>
	lduSolverPerformance fvMatrix<scalar>::solve
	(
		const dictionary&
	);

	template<>
	tmp<Field<scalar>> fvMatrix<scalar>::residual() const;

	template<>
	tmp<volScalarField> fvMatrix<scalar>::H() const;

	template<>
	tmp<volScalarField> fvMatrix<scalar>::H1() const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvScalarMatrix_Header
