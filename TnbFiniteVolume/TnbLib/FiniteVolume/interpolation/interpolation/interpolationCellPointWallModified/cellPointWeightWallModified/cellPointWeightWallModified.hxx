#pragma once
#ifndef _cellPointWeightWallModified_Header
#define _cellPointWeightWallModified_Header

#include <cellPointWeight.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;

	/*---------------------------------------------------------------------------*\
					 Class cellPointWeightWallModified Declaration
	\*---------------------------------------------------------------------------*/

	class cellPointWeightWallModified
		:
		public cellPointWeight
	{
	public:

		// Constructors

			//- Construct from components
		cellPointWeightWallModified
		(
			const polyMesh& mesh,
			const vector& position,
			const label nCell,
			const label facei = -1
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellPointWeightWallModified_Header
