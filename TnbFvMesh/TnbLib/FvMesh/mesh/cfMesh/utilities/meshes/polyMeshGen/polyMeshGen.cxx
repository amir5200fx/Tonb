#include <polyMeshGen.hxx>

#include <demandDrivenData.hxx>
#include <OFstream.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	polyMeshGen::polyMeshGen(const Time& t)
		:
		polyMeshGenCells(t),
		metaDict_
		(
			IOobject
			(
				"meshMetaDict",
				runTime_.constant(),
				"polyMesh",
				runTime_,
				IOobject::READ_IF_PRESENT,
				IOobject::NO_WRITE
			)
		)
	{}

	//- Construct from components without the boundary
	polyMeshGen::polyMeshGen
	(
		const Time& t,
		const pointField& points,
		const faceList& faces,
		const cellList& cells
	)
		:
		polyMeshGenCells(t, points, faces, cells),
		metaDict_
		(
			IOobject
			(
				"meshMetaDict",
				runTime_.constant(),
				"polyMesh",
				runTime_,
				IOobject::READ_IF_PRESENT,
				IOobject::NO_WRITE
			)
		)
	{}

	//- Construct from components with the boundary
	polyMeshGen::polyMeshGen
	(
		const Time& t,
		const pointField& points,
		const faceList& faces,
		const cellList& cells,
		const wordList& patchNames,
		const labelList& patchStart,
		const labelList& nFacesInPatch
	)
		:
		polyMeshGenCells
		(
			t,
			points,
			faces,
			cells,
			patchNames,
			patchStart,
			nFacesInPatch
		),
		metaDict_
		(
			IOobject
			(
				"meshMetaDict",
				runTime_.constant(),
				"polyMesh",
				runTime_,
				IOobject::READ_IF_PRESENT,
				IOobject::NO_WRITE
			)
		)
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Destructor
	polyMeshGen::~polyMeshGen()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void polyMeshGen::read()
	{
		polyMeshGenCells::read();
	}

	void polyMeshGen::write() const
	{
		//- remove old mesh before writting
		const fileName meshDir = runTime_.path() / runTime_.constant() / "polyMesh";

		rm(meshDir / "points");
		rm(meshDir / "faces");
		rm(meshDir / "owner");
		rm(meshDir / "neighbour");
		rm(meshDir / "cells");
		rm(meshDir / "boundary");
		rm(meshDir / "pointZones");
		rm(meshDir / "faceZones");
		rm(meshDir / "cellZones");
		rm(meshDir / "meshModifiers");
		rm(meshDir / "parallelData");
		rm(meshDir / "meshMetaDict");

		// remove sets if they exist
		if (isDir(meshDir / "sets"))
		{
			rmDir(meshDir / "sets");
		}

		//- write the mesh
		polyMeshGenCells::write();

		//- write meta data
		OFstream fName(meshDir / "meshMetaDict");

		metaDict_.writeHeader(fName);
		metaDict_.writeData(fName);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //