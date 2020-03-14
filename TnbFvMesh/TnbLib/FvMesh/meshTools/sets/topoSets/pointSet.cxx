#include <pointSet.hxx>

#include <mapPolyMesh.hxx>
#include <polyMesh.hxx>
#include <syncTools.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(pointSet, 0);

	addToRunTimeSelectionTable(topoSet, pointSet, word);
	addToRunTimeSelectionTable(topoSet, pointSet, size);
	addToRunTimeSelectionTable(topoSet, pointSet, set);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	pointSet::pointSet(const IOobject& obj)
		:
		topoSet(obj, typeName)
	{}


	pointSet::pointSet
	(
		const polyMesh& mesh,
		const word& name,
		readOption r,
		writeOption w
	)
		:
		topoSet(mesh, typeName, name, r, w)
	{
		// Sets can contain retired points.  HJ, 17/Aug/2015
		check(mesh.allPoints().size());
	}


	pointSet::pointSet
	(
		const polyMesh& mesh,
		const word& name,
		const label size,
		writeOption w
	)
		:
		topoSet(mesh, name, size, w)
	{}


	pointSet::pointSet
	(
		const polyMesh& mesh,
		const word& name,
		const topoSet& set,
		writeOption w
	)
		:
		topoSet(mesh, name, set, w)
	{}


	pointSet::pointSet
	(
		const polyMesh& mesh,
		const word& name,
		const labelHashSet& set,
		writeOption w
	)
		:
		topoSet(mesh, name, set, w)
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	pointSet::~pointSet()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void pointSet::sync(const polyMesh& mesh)
	{
		// Convert to boolList

		boolList contents(mesh.nPoints(), false);

		forAllConstIter(pointSet, *this, iter)
		{
			contents[iter.key()] = true;
		}
		syncTools::syncPointList
		(
			mesh,
			contents,
			orEqOp<bool>(),
			false,          // null value
			false           // no separation
		);

		// Convert back to labelHashSet

		labelHashSet newContents(size());

		forAll(contents, pointI)
		{
			if (contents[pointI])
			{
				newContents.insert(pointI);
			}
		}

		transfer(newContents);
	}


	label pointSet::maxSize(const polyMesh& mesh) const
	{
		return mesh.allPoints().size();
	}


	void pointSet::updateMesh(const mapPolyMesh& morphMap)
	{
		updateLabels(morphMap.reversePointMap());
	}


	void pointSet::writeDebug
	(
		Ostream& os,
		const primitiveMesh& mesh,
		const label maxLen
	) const
	{
		topoSet::writeDebug(os, mesh.points(), maxLen);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //