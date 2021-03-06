#pragma once
#ifndef _PBiCCCG_Header
#define _PBiCCCG_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::PBiCCCG

Description
	Preconditioned bi-conjugate gradient solver for asymmetric lduMatrices
	using a run-time selectable preconditioner.

SourceFiles
	PBiCCCG.C

\*---------------------------------------------------------------------------*/

#include <LduMatrixTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class PBiCCCG Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type, class DType, class LUType>
	class PBiCCCG
		:
		public LduMatrix<Type, DType, LUType>::solver
	{

	public:

		//- Runtime type information
		//TypeName("PBiCCCG");
		static const char* typeName_() { return "PBiCCCG"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from matrix components and solver data dictionary
		PBiCCCG
		(
			const word& fieldName,
			const LduMatrix<Type, DType, LUType>& matrix,
			const dictionary& solverDict
		);

		//- Disallow default bitwise copy construction
		PBiCCCG(const PBiCCCG&) = delete;


		// Destructor

		virtual ~PBiCCCG()
		{}


		// Member Functions

			//- Solve the matrix with this solver
		virtual SolverPerformance<Type> solve(Field<Type>& psi) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const PBiCCCG&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <PBiCCCGI.hxx>

//#ifdef NoRepository
//#include <PBiCCCG.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PBiCCCG_Header
