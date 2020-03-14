#include <cellSet.hxx>

#include <mapPolyMesh.hxx>
#include <polyMesh.hxx>
#include <tnbTime.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(cellSet, 0);

	addToRunTimeSelectionTable(topoSet, cellSet, word);
	addToRunTimeSelectionTable(topoSet, cellSet, size);
	addToRunTimeSelectionTable(topoSet, cellSet, set);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	cellSet::cellSet(const IOobject& obj)
		:
		topoSet(obj, typeName)
	{}


	cellSet::cellSet
	(
		const polyMesh& mesh,
		const word& name,
		readOption r,
		writeOption w
	)
		:
		topoSet(mesh, typeName, name, r, w)
	{
		// Make sure set within valid range: there are no retired cells
		check(mesh.nCells());
	}


	cellSet::cellSet
	(
		const polyMesh& mesh,
		const word& name,
		const label size,
		writeOption w
	)
		:
		topoSet(mesh, name, size, w)
	{}


	cellSet::cellSet
	(
		const polyMesh& mesh,
		const word& name,
		const topoSet& set,
		writeOption w
	)
		:
		topoSet(mesh, name, set, w)
	{}


	cellSet::cellSet
	(
		const polyMesh& mesh,
		const word& name,
		const labelHashSet& set,
		writeOption w
	)
		:
		topoSet(mesh, name, set, w)
	{}


	// Database constructors (for when no mesh available)
	cellSet::cellSet
	(
		const Time& runTime,
		const word& name,
		readOption r,
		writeOption w
	)
		:
		topoSet
		(
			IOobject
			(
				name,
				runTime.findInstance(polyMesh::meshSubDir, "faces"),
				polyMesh::meshSubDir / "sets",
				runTime,
				r,
				w
			),
			typeName
		)
	{}


	cellSet::cellSet
	(
		const Time& runTime,
		const word& name,
		const label size,
		writeOption w
	)
		:
		topoSet
		(
			IOobject
			(
				name,
				runTime.findInstance(polyMesh::meshSubDir, "faces"),
				polyMesh::meshSubDir / "sets",
				runTime,
				NO_READ,
				w
			),
			size
		)
	{}


	cellSet::cellSet
	(
		const Time& runTime,
		const word& name,
		const labelHashSet& set,
		writeOption w
	)
		:
		topoSet
		(
			IOobject
			(
				name,
				runTime.findInstance(polyMesh::meshSubDir, "faces"),
				polyMesh::meshSubDir / "sets",
				runTime,
				NO_READ,
				w
			),
			set
		)
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	cellSet::~cellSet()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	label cellSet::maxSize(const polyMesh& mesh) const
	{
		return mesh.nCells();
	}


	void cellSet::updateMesh(const mapPolyMesh& morphMap)
	{
		updateLabels(morphMap.reverseCellMap());
	}


	void tnbLib::cellSet::writeDebug
	(
		Ostream& os,
		const primitiveMesh& mesh,
		const label maxLen
	) const
	{
		topoSet::writeDebug(os, mesh.cellCentres(), maxLen);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //