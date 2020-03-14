#include <faceSet.hxx>

#include <mapPolyMesh.hxx>
#include <polyMesh.hxx>
#include <processorPolyPatch.hxx>
#include <cyclicPolyPatch.hxx>
#include <IPstream.hxx>
#include <OPstream.hxx>
#include <PstreamReduceOps.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(faceSet, 0);

	addToRunTimeSelectionTable(topoSet, faceSet, word);
	addToRunTimeSelectionTable(topoSet, faceSet, size);
	addToRunTimeSelectionTable(topoSet, faceSet, set);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	faceSet::faceSet(const IOobject& obj)
		:
		topoSet(obj, typeName)
	{}


	faceSet::faceSet
	(
		const polyMesh& mesh,
		const word& name,
		readOption r,
		writeOption w
	)
		:
		topoSet(mesh, typeName, name, r, w)
	{
		// Sets can also contain retired faces.  HJ, 17/Aug/2015
		check(mesh.allFaces().size());
	}


	faceSet::faceSet
	(
		const polyMesh& mesh,
		const word& name,
		const label size,
		writeOption w
	)
		:
		topoSet(mesh, name, size, w)
	{}


	faceSet::faceSet
	(
		const polyMesh& mesh,
		const word& name,
		const topoSet& set,
		writeOption w
	)
		:
		topoSet(mesh, name, set, w)
	{}


	faceSet::faceSet
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

	faceSet::~faceSet()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void faceSet::sync(const polyMesh& mesh)
	{
		const polyBoundaryMesh& patches = mesh.boundaryMesh();

		label nAdded = 0;

		if (Pstream::parRun())
		{
			// Send faces in set that are on a processorPatch. Send as patch face
			// indices.
			forAll(patches, patchI)
			{
				const polyPatch& pp = patches[patchI];

				if (isA<processorPolyPatch>(pp))
				{
					const processorPolyPatch& procPatch =
						refCast<const processorPolyPatch>(pp);

					// Convert faceSet locally to labelList.
					dynamicLabelList setFaces(pp.size());

					forAll(pp, i)
					{
						if (found(pp.start() + i))
						{
							setFaces.append(i);
						}
					}
					setFaces.shrink();

					OPstream toNeighbour
					(
						Pstream::blocking,
						procPatch.neighbProcNo()
					);

					toNeighbour << setFaces;
				}
			}

			// Receive
			forAll(patches, patchI)
			{
				const polyPatch& pp = patches[patchI];

				if (isA<processorPolyPatch>(pp))
				{
					const processorPolyPatch& procPatch =
						refCast<const processorPolyPatch>(pp);

					IPstream fromNeighbour
					(
						Pstream::blocking,
						procPatch.neighbProcNo()
					);

					labelList setFaces(fromNeighbour);

					forAll(setFaces, i)
					{
						if (insert(pp.start() + setFaces[i]))
						{
							nAdded++;
						}
					}
				}
			}
		}

		// Couple cyclic patches
		forAll(patches, patchI)
		{
			const polyPatch& pp = patches[patchI];

			if (isA<cyclicPolyPatch>(pp))
			{
				const cyclicPolyPatch& cycPatch =
					refCast<const cyclicPolyPatch>(pp);

				forAll(cycPatch, i)
				{
					label thisFaceI = cycPatch.start() + i;
					label otherFaceI = cycPatch.transformGlobalFace(thisFaceI);

					if (found(thisFaceI))
					{
						if (insert(otherFaceI))
						{
							nAdded++;
						}
					}
					else if (found(otherFaceI))
					{
						if (insert(thisFaceI))
						{
							nAdded++;
						}
					}
				}
			}
		}


		reduce(nAdded, sumOp<label>());

		//if (nAdded > 0)
		//{
		//    Info<< "Added an additional " << nAdded
		//        << " faces on coupled patches. "
		//        << "(processorPolyPatch, cyclicPolyPatch)" << endl;
		//}
	}


	label faceSet::maxSize(const polyMesh& mesh) const
	{
		return mesh.allFaces().size();
	}


	void faceSet::updateMesh(const mapPolyMesh& morphMap)
	{
		updateLabels(morphMap.reverseFaceMap());
	}


	void faceSet::writeDebug
	(
		Ostream& os,
		const primitiveMesh& mesh,
		const label maxLen
	) const
	{
		topoSet::writeDebug(os, mesh.faceCentres(), maxLen);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //