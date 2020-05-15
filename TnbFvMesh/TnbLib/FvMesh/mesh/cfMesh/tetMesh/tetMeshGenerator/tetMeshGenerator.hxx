#pragma once
#ifndef _tetMeshGenerator_Header
#define _tetMeshGenerator_Header

#include <polyMeshGen.hxx>
#include <IOdictionary.hxx>
#include <workflowControls.hxx>

//#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declarations
	class triSurf;
	class meshOctree;
	class Time;

	/*---------------------------------------------------------------------------*\
							   Class tetMeshGenerator Declaration
	\*---------------------------------------------------------------------------*/

	class tetMeshGenerator
	{
		// Private data
			//- reference to Time
		const Time& runTime_;

		//- pointer to the surface
		const triSurf* surfacePtr_;

		//- pointer to the modified surface mesh
		const triSurf* modSurfacePtr_;

		//- IOdictionary containing information about cell sizes, etc..
		IOdictionary meshDict_;

		//- pointer to the octree
		meshOctree* octreePtr_;

		//- mesh
		polyMeshGen mesh_;

		//- workflow controller
		workflowControls controller_;

		// Private member functions
			//- create cartesian mesh
		void createTetMesh();

		//- prepare mesh surface
		void surfacePreparation();

		//- map mesh to the surface and untangle surface
		void mapMeshToSurface();

		//- capture edges and corners
		void extractPatches();

		//- capture edges and corners
		void mapEdgesAndCorners();

		//- optimise surface mesh
		void optimiseMeshSurface();

		//- add boundary layers
		void generateBoundaryLayers();

		//- mesh optimisation
		void optimiseFinalMesh();

		//- re-project points back on the surface mesh after back-scaling
		void projectSurfaceAfterBackScaling();

		//- refine boundary layers
		void refBoundaryLayers();

		//- replace boundaries
		void replaceBoundaries();

		//- renumber the mesh
		void renumberMesh();

		//- generate mesh
		void generateMesh();

		//- Disallow default bitwise copy construct
		tetMeshGenerator(const tetMeshGenerator&);

		//- Disallow default bitwise assignment
		void operator=(const tetMeshGenerator&);

	public:

		// Constructors

			//- Construct from time
		tetMeshGenerator(const Time&);

		// Destructor

		~tetMeshGenerator();


		// Member Functions

			//- write the mesh
		void writeMesh() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tetMeshGenerator_Header
