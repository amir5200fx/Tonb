#pragma once
#ifndef _matrix2D_Header
#define _matrix2D_Header

#include <scalar.hxx>
#include <FixedList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class matrix2D Declaration
	\*---------------------------------------------------------------------------*/

	class matrix2D
		: public FixedList<FixedList<scalar, 2>, 2>
	{
		// Private members
		scalar det_;
		bool calculatedDet_;

		// Private member functions
			//- calculate matrix determinant
		inline void calculateDeterminant();

	public:

		// Constructors
			//- Null constructor
		explicit inline matrix2D();

		//- Copy constructor
		inline matrix2D(const matrix2D&);

		// Destructor
		inline ~matrix2D();

		// Member functions
			//- return matrix determinant
		inline scalar determinant();

		//- return inverse matrix
		inline matrix2D inverse();

		//- find the solution of the system with the given rhs
		inline FixedList<scalar, 2> solve
		(
			const FixedList<scalar, 2>& source
		);

		//- return the first component of the solution vector
		inline scalar solveFirst(const FixedList<scalar, 2>& source);

		//- return the second component of the solution vector
		inline scalar solveSecond(const FixedList<scalar, 2>& source);
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <matrix2DI.hxx>

#endif // !_matrix2D_Header
