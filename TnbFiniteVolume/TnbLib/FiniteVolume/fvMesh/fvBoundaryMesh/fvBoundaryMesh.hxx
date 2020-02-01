#pragma once
#ifndef _fvBoundaryMesh_Header
#define _fvBoundaryMesh_Header

#include <fvPatchList.hxx>
#include <lduInterfacePtrsList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;
	class polyBoundaryMesh;

	/*---------------------------------------------------------------------------*\
							   Class fvBoundaryMesh Declaration
	\*---------------------------------------------------------------------------*/

	class fvBoundaryMesh
		:
		public fvPatchList
	{
	private:

		// Private data

			//- Reference to mesh
		const fvMesh& mesh_;


		// Private Member Functions

			//- Disable default copy construct
		fvBoundaryMesh(const fvBoundaryMesh&);

		//- Disallow assignment
		void operator=(const fvBoundaryMesh&);

		//- Add fvPatches corresponding to the given polyBoundaryMesh
		void addPatches(const polyBoundaryMesh&);


	protected:

		//- Update boundary based on new polyBoundaryMesh
		void readUpdate(const polyBoundaryMesh&);


	public:

		friend class fvMesh;


		// Constructors

			//- Construct with zero size
		fvBoundaryMesh
		(
			const fvMesh&
		);

		//- Construct from polyBoundaryMesh
		fvBoundaryMesh
		(
			const fvMesh&,
			const polyBoundaryMesh&
		);


		// Member functions

			// Access

				//- Return the mesh reference
		const fvMesh& mesh() const
		{
			return mesh_;
		}

		//- Return a list of pointers for each patch
		//  with only those pointing to interfaces being set
		lduInterfacePtrsList interfaces() const;


		//- Correct patches after moving points
		void movePoints();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvBoundaryMesh_Header
