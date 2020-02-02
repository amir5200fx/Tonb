#pragma once
#ifndef _cellPointWeight_Header
#define _cellPointWeight_Header

#include <vector.hxx>
#include <FixedList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;

	/*---------------------------------------------------------------------------*\
							   Class cellPointWeight Declaration
	\*---------------------------------------------------------------------------*/

	class cellPointWeight
	{
	protected:

		// Protected data

		   //- Cell index
		const label cellIndex_;

		//- Weights applied to tet vertices
		FixedList<scalar, 4> weights_;

		//- Face vertex indices
		FixedList<label, 3> faceVertices_;


		// Protected Member Functions

		void findTetrahedron
		(
			const polyMesh& mesh,
			const vector& position,
			const label cellIndex
		);

		void findTriangle
		(
			const polyMesh& mesh,
			const vector& position,
			const label faceIndex
		);


	public:

		//- Debug switch
		static debug::debugSwitch debug;

		//- Tolerance used in calculating barycentric co-ordinates
		//  (applied to normailised values)
		static scalar tol;


		// Constructors

			//- Construct from components
		cellPointWeight
		(
			const polyMesh& mesh,
			const vector& position,
			const label nCell,
			const label facei = -1
		);


		// Member Functions

			//- Cell index
		inline label cell() const
		{
			return cellIndex_;
		}

		//- interpolation weights
		inline const FixedList<scalar, 4>& weights() const
		{
			return weights_;
		}

		//- interpolation addressing for points on face
		inline const FixedList<label, 3>& faceVertices() const
		{
			return faceVertices_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellPointWeight_Header
