#pragma once
#ifndef _interpolationCellPointWallModified_Header
#define _interpolationCellPointWallModified_Header

#include <interpolationCellPoint.hxx>
#include <cellPointWeightWallModified.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class interpolationCellPoint Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class interpolationCellPointWallModified
		:
		public interpolationCellPoint<Type>
	{
	public:

		//- Runtime type information
		TypeName("cellPointWallModified");


		// Constructors

			//- Construct from components
		interpolationCellPointWallModified
		(
			const GeometricField<Type, fvPatchField, volMesh>& psi
		);


		// Member Functions

			//- Interpolate field for the given cellPointWeight
		inline Type interpolate(const cellPointWeightWallModified& cpw) const;

		//- Interpolate field to the given point in the given cell
		inline Type interpolate
		(
			const vector& position,
			const label nCell,
			const label facei = -1
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <interpolationCellPointWallModifiedI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <interpolationCellPointWallModified.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interpolationCellPointWallModified_Header
