#pragma once
#ifndef _meshSurfaceEngineModifier_Header
#define _meshSurfaceEngineModifier_Header

#include <meshSurfaceEngine.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class meshSurfaceEngineModifier Declaration
	\*---------------------------------------------------------------------------*/

	class meshSurfaceEngineModifier
	{
		// Private data
			//- reference to the meshSurfaceEngine
		meshSurfaceEngine& surfaceEngine_;

		//- Disallow default bitwise copy construct
		meshSurfaceEngineModifier(const meshSurfaceEngineModifier&);

		//- Disallow default bitwise assignment
		void operator=(const meshSurfaceEngineModifier&);

	public:

		// Constructors

			//- Construct from reference to meshSurfaceEngine
		meshSurfaceEngineModifier(meshSurfaceEngine& surfaceEngine);

		//- Construct from const reference to meshSurfaceEngine
		meshSurfaceEngineModifier(const meshSurfaceEngine& surfaceEngine);

		// Destructor

		~meshSurfaceEngineModifier();

		// Member Functions

			//- relocate the selected boundary vertex
		void moveBoundaryVertexNoUpdate(const label bpI, const point& newP);

		//- relocate the selected boundary vertex and update geometry data
		void moveBoundaryVertex(const label bpI, const point& newP);

		//- update normals of boundary vertices at processor boundaries
		inline void updateVertexNormals()
		{
			if (surfaceEngine_.pointNormalsPtr_)
				surfaceEngine_.updatePointNormalsAtProcBoundaries();
		}

		//- updates faceCentres, face normal, and point normals
		//- of the boundary faces attached to the selected boundary points
		void updateGeometry(const labelLongList&);
		void updateGeometry();

		//- makes sure that all surface vertices at parallel boundaries
		//- have the same coordinates
		void syncVerticesAtParallelBoundaries();
		void syncVerticesAtParallelBoundaries(const labelLongList&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_meshSurfaceEngineModifier_Header
