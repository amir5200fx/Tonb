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
	tnbLib::smoothSolver

Description
	Iterative solver for symmetric and assymetric matrices which uses a
	run-time selected smoother e.g. GaussSeidel to converge the solution to
	the required tolerance.

	To improve efficiency, the residual is evaluated after every nSweeps
	smoothing iterations.

SourceFiles
	smoothSolver.C

\*---------------------------------------------------------------------------*/
#ifndef _smoothSolver_Header
#define _smoothSolver_Header

#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class smoothSolver Declaration
	\*---------------------------------------------------------------------------*/

	class smoothSolver
		:
		public lduSolver
	{
	protected:

		// Protected data

			//- Number of sweeps before the evaluation of residual
		label nSweeps_;

		//- Read the control parameters from the dictionary
		virtual void readControls();


	public:

		//- Runtime type information
		TypeName("smoothSolver");


		// Constructors

			//- Construct from matrix components and solver controls
		smoothSolver
		(
			const word& fieldName,
			const lduMatrix& matrix,
			const FieldField<Field, scalar>& coupleBouCoeffs,
			const FieldField<Field, scalar>& coupleIntCoeffs,
			const lduInterfaceFieldPtrsList& interfaces,
			const dictionary& dict
		);


		// Destructor

		virtual ~smoothSolver()
		{}

		// Member Functions

			//- Solve the matrix with this solver
		virtual lduSolverPerformance solve
		(
			scalarField& x,
			const scalarField& b,
			const direction cmpt = 0
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_smoothSolver_Header
