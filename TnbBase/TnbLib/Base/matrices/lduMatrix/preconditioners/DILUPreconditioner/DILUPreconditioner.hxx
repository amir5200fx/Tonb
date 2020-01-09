#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.0
	\\  /    A nd           | Web:         http://www.foam-extend.org
	 \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
	This file is part of foam-extend.

	foam-extend is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the
	Free Software Foundation, either version 3 of the License, or (at your
	option) any later version.

	foam-extend is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::DILUPreconditioner

Description
	Simplified diagonal-based incomplete LU preconditioner for asymmetric
	matrices.  The reciprocal of the preconditioned diagonal is calculated
	and stored.

SourceFiles
	DILUPreconditioner.C

\*---------------------------------------------------------------------------*/
#ifndef _DILUPreconditioner_Header
#define _DILUPreconditioner_Header

#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class DILUPreconditioner Declaration
	\*---------------------------------------------------------------------------*/

	class DILUPreconditioner
		:
		public lduPreconditioner
	{
		// Private data

			//- The reciprocal preconditioned diagonal
		scalarField rD_;


	public:

		//- Runtime type information
		TypeName("DILU");


		// Constructors

			//- Construct from matrix components and preconditioner solver controls
		DILUPreconditioner
		(
			const lduMatrix& matrix,
			const FieldField<Field, scalar>& coupleBouCoeffs,
			const FieldField<Field, scalar>& coupleIntCoeffs,
			const lduInterfaceFieldPtrsList& interfaces,
			const dictionary& dict
		);


		// Destructor

		virtual ~DILUPreconditioner()
		{}


		// Member Functions

			//- Calculate the reciprocal of the preconditioned diagonal
		static void calcReciprocalD(scalarField& rD, const lduMatrix& matrix);

		//- Execute preconditioning
		virtual void precondition
		(
			scalarField& wA,
			const scalarField& rA,
			const direction cmpt = 0
		) const;

		//- Execute preconditioning with matrix transpose
		virtual void preconditionT
		(
			scalarField& wT,
			const scalarField& rT,
			const direction cmpt = 0
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_DILUPreconditioner_Header
