#pragma once
#ifndef _interpolationCell_Header
#define _interpolationCell_Header

#include <interpolation.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	/*---------------------------------------------------------------------------*\
						  Class interpolationCell Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class interpolationCell
		:
		public interpolation<Type>
	{

	public:

		//- Runtime type information
		TypeName("cell");


		// Constructors

			//- Construct from components
		interpolationCell
		(
			const GeometricField<Type, fvPatchField, volMesh>& psi
		);


		// Member Functions

			//- Interpolate field to the given point in the given cell
		Type interpolate
		(
			const vector& position,
			const label nCell,
			const label facei = -1
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <interpolationCell.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interpolationCell_Header
