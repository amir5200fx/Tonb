#pragma once
#ifndef _partTetMeshSimplex_Header
#define _partTetMeshSimplex_Header

#include <partTetMesh.hxx>
#include <parPartTet.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declarations
	class partTetMesh;

	/*---------------------------------------------------------------------------*\
							   Class partTetMeshSimplex Declaration
	\*---------------------------------------------------------------------------*/

	class partTetMeshSimplex
	{
		// Private data
			//- points making the simplex
		DynList<point, 128> pts_;

		//- tets making the simplex
		DynList<partTet, 128> tets_;

	public:

		// Constructors
			//- Construct from partTetMeshSimplex and point label
		partTetMeshSimplex(const partTetMesh& tm, const label pI);

		//- Construct from the list of parPartTet and point label
		partTetMeshSimplex
		(
			const DynList<parPartTet>& pt,
			const label gpI
		);

		//- contruct from a list of points and a list of partTets
		//- ad a point label
		partTetMeshSimplex
		(
			const DynList<point, 128>& pts,
			const DynList<partTet, 128>& tets,
			const label pointI
		);

		// Destructor
		~partTetMeshSimplex();

		// Member functions
			//- return points
		inline DynList<point, 128>& pts()
		{
			return pts_;
		}

		//- return points
		inline const DynList<point, 128>& pts() const
		{
			return pts_;
		}

		//- return tets
		inline const DynList<partTet, 128>& tets() const
		{
			return tets_;
		}

		//- return centre point coordinates
		inline const point& centrePoint() const
		{
			return pts_[tets_[0][3]];
		}
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <partTetMeshSimplexI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_partTetMeshSimplex_Header
