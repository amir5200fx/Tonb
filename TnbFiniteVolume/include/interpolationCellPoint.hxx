#pragma once
#ifndef _interpolationCellPoint_Header
#define _interpolationCellPoint_Header

#include <interpolation.hxx>
#include <cellPointWeight.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class interpolationCellPoint Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class interpolationCellPoint
		:
		public interpolation<Type>
	{
	protected:

		// Protected data

			//- Interpolated volfield
		const GeometricField<Type, pointPatchField, pointMesh> psip_;


	public:

		//- Runtime type information
		TypeName("cellPoint");


		// Constructors

			//- Construct from components
		interpolationCellPoint
		(
			const GeometricField<Type, fvPatchField, volMesh>& psi
		);


		// Member Functions

			//- Interpolate field for the given cellPointWeight
		inline Type interpolate(const cellPointWeight& cpw) const;

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

#include <interpolationCellPointI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <interpolationCellPoint.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interpolationCellPoint_Header
