#pragma once
#ifndef _interpolationCellPointFace_Header
#define _interpolationCellPointFace_Header

#include <interpolation.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class interpolationCellPointFace Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class interpolationCellPointFace
		:
		public interpolation<Type>
	{
		// Private data

			//- Interpolated volfield
		const GeometricField<Type, pointPatchField, pointMesh> psip_;

		//- Linearly interpolated volfield
		const GeometricField<Type, fvsPatchField, surfaceMesh> psis_;

		bool findTet
		(
			const vector& position,
			const label nFace,
			vector tetPoints[],
			label tetLabelCandidate[],
			label tetPointLabels[],
			scalar phi[],
			scalar phiCandidate[],
			label& closestFace,
			scalar& minDistance
		) const;

		bool findTriangle
		(
			const vector& position,
			const label nFace,
			label tetPointLabels[],
			scalar phi[]
		) const;


	public:

		//- Runtime type information
		TypeName("cellPointFace");


		// Constructors

			//- Construct from components
		interpolationCellPointFace
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
#   include <interpolationCellPointFace.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interpolationCellPointFace_Header
