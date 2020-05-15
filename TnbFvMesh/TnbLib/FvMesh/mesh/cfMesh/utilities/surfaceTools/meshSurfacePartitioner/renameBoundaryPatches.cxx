#include <renameBoundaryPatches.hxx>

#include <demandDrivenData.hxx>
#include <IOdictionary.hxx>

#include <map>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void renameBoundaryPatches::calculateNewBoundary()
	{
		Info << "Renaming boundary patches" << endl;

		const dictionary& dict = meshDict_.subDict("renameBoundary");

		std::map<word, label> patchToLabel;
		forAll(mesh_.boundaries(), patchI)
		{
			patchToLabel.insert
			(
				std::pair<word, label>
				(
					mesh_.boundaries()[patchI].patchName(),
					patchI
					)
			);
		}

		labelList patchToNew(mesh_.boundaries().size(), -1);

		wordList newPatchNames(patchToNew.size());
		wordList newPatchTypes(patchToNew.size());
		std::map<word, label> newNameToPos;
		label newPatchI(0);

		//- read new patch names and types
		if (dict.found("newPatchNames"))
		{
			PtrList<entry> patchesToRename;

			if (dict.isDict("newPatchNames"))
			{
				const dictionary& newPatchNames = dict.subDict("newPatchNames");
				const wordList keys = newPatchNames.toc();

				patchesToRename.setSize(keys.size());

				forAll(keys, patchI)
					patchesToRename.set
					(
						patchI,
						newPatchNames.lookupEntry
						(
							keys[patchI],
							false,
							false
						).clone()
					);
			}
			else
			{
				PtrList<entry> copyPatchesToRename(dict.lookup("newPatchNames"));
				patchesToRename.transfer(copyPatchesToRename);
			}

			forAll(patchesToRename, patchI)
			{
				const word patchName = patchesToRename[patchI].keyword();

				const labelList matchedPatches = mesh_.findPatches(patchName);

				if (matchedPatches.empty())
				{
					Warning << "No matches for " << patchName << " found!!" << endl;
					continue;
				}

				if (!patchesToRename[patchI].isDict())
				{
					Warning << "Cannot rename patch " << patchName << endl;
					Warning << "This is due to incorrect settings! Exitting."
						<< endl;
					return;
				}

				const dictionary pDict = patchesToRename[patchI].dict();

				forAll(matchedPatches, matchI)
				{
					word newName(mesh_.getPatchName(matchedPatches[matchI]));

					if (pDict.found("newName"))
						newName = word(pDict.lookup("newName"));

					if (newNameToPos.find(newName) != newNameToPos.end())
					{
						//- patch with the same name already exists
						patchToNew[matchedPatches[matchI]] = newNameToPos[newName];
						continue;
					}

					//- add a new patch
					newNameToPos.insert(std::pair<word, label>(newName, newPatchI));
					newPatchNames[newPatchI] = newName;
					if (pDict.found("type"))
					{
						const word newType(pDict.lookup("type"));
						newPatchTypes[newPatchI] = newType;
					}
					else
					{
						newPatchTypes[newPatchI] = "wall";
					}

					patchToNew[matchedPatches[matchI]] = newPatchI;
					++newPatchI;
				}
			}
		}

		word defaultName("walls");
		if (dict.found("defaultName"))
			defaultName = word(dict.lookup("defaultName"));
		word defaultType("wall");
		if (dict.found("defaultType"))
			defaultType = word(dict.lookup("defaultType"));

		if (dict.found("defaultName") && (newPatchI < patchToNew.size()))
		{
			bool addPatch(false);
			forAll(patchToNew, patchI)
				if (patchToNew[patchI] == -1)
				{
					addPatch = true;
					break;
				}

			if (addPatch)
			{
				newNameToPos.insert(std::pair<word, label>(defaultName, newPatchI));
				newPatchNames[newPatchI] = defaultName;
				newPatchTypes[newPatchI] = defaultType;
				++newPatchI;
			}
		}
		else
		{
			forAll(patchToNew, patchI)
			{
				if (patchToNew[patchI] != -1)
					continue;

				patchToNew[patchI] = newPatchI;
				newPatchNames[newPatchI] = mesh_.boundaries()[patchI].patchName();
				newPatchTypes[newPatchI] = mesh_.boundaries()[patchI].patchType();
				++newPatchI;
			}
		}

		if (newPatchI == 0)
			return;

		newPatchNames.setSize(newPatchI);
		newPatchTypes.setSize(newPatchI);

		//- start creating new boundary
		VRWGraph newBoundaryFaces;
		labelLongList newBoundaryOwners;
		labelLongList newBoundaryPatches;

		const PtrList<boundaryPatch>& boundaries = mesh_.boundaries();
		const faceListPMG& faces = mesh_.faces();
		const labelList& owner = mesh_.owner();
		forAll(boundaries, patchI)
		{
			const boundaryPatch& wp = boundaries[patchI];
			const label start = wp.patchStart();
			const label end = start + wp.patchSize();

			if (patchToNew[patchI] == -1)
			{
				//- this patch is moved to the default patch
				for (label faceI = start; faceI < end; ++faceI)
				{
					newBoundaryFaces.appendList(faces[faceI]);
					newBoundaryPatches.append(newPatchI - 1);
					newBoundaryOwners.append(owner[faceI]);
				}
			}
			else
			{
				//- this patch is renamed
				for (label faceI = start; faceI < end; ++faceI)
				{
					newBoundaryFaces.appendList(faces[faceI]);
					newBoundaryPatches.append(patchToNew[patchI]);
					newBoundaryOwners.append(owner[faceI]);
				}
			}
		}

		//- execute the modifier
		polyMeshGenModifier meshModifier(mesh_);
		meshModifier.replaceBoundary
		(
			newPatchNames,
			newBoundaryFaces,
			newBoundaryOwners,
			newBoundaryPatches
		);
		forAll(meshModifier.boundariesAccess(), patchI)
			meshModifier.boundariesAccess()[patchI].patchType() =
			newPatchTypes[patchI];

		Info << "Finished renaming boundary patches" << endl;
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	renameBoundaryPatches::renameBoundaryPatches
	(
		polyMeshGen& mesh,
		const IOdictionary& meshDict
	)
		:
		mesh_(mesh),
		meshDict_(meshDict)
	{
		if (meshDict.found("renameBoundary"))
			calculateNewBoundary();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	renameBoundaryPatches::~renameBoundaryPatches()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //