#include <cyclicAMGInterface.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <SLList.hxx>
#include <Hash.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		AMGInterface,
		cyclicAMGInterface,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicAMGInterface::cyclicAMGInterface
(
	const lduPrimitiveMesh& lduMesh,
	const lduInterface& fineInterface,
	const labelField& localRestrictAddressing,
	const labelField& neighbourRestrictAddressing
)
	:
	AMGInterface(lduMesh),
	fineCyclicInterface_(refCast<const cyclicLduInterface>(fineInterface))
{
	// Make a lookup table of entries for owner/neighbour
	HashTable<SLList<label>, label, Hash<label> > neighboursTable
	(
		localRestrictAddressing.size()
	);

	// Table of face-sets to be agglomerated
	HashTable<SLList<SLList<label> >, label, Hash<label> > faceFaceTable
	(
		localRestrictAddressing.size()
	);

	label nCoarseFaces = 0;

	label sizeBy2 = localRestrictAddressing.size() / 2;

	for (label ffi = 0; ffi < sizeBy2; ffi++)
	{
		label curMaster = localRestrictAddressing[ffi];
		label curSlave = localRestrictAddressing[ffi + sizeBy2];

		// Look for the master cell.  If it has already got a face,
		// add the coefficient to the face.  If not, create a new
		// face.
		if (neighboursTable.found(curMaster))
		{
			// Check all current neighbours to see if the current
			// slave already exists.  If so, add the coefficient.

			SLList<label>& curNbrs = neighboursTable.find(curMaster)();

			SLList<SLList<label> >& curFaceFaces =
				faceFaceTable.find(curMaster)();

			bool nbrFound = false;

			SLList<label>::iterator nbrsIter = curNbrs.begin();

			SLList<SLList<label> >::iterator faceFacesIter =
				curFaceFaces.begin();

			for
				(
					;
					nbrsIter != curNbrs.end(), faceFacesIter != curFaceFaces.end();
					++nbrsIter, ++faceFacesIter
					)
			{
				if (nbrsIter() == curSlave)
				{
					nbrFound = true;
					faceFacesIter().append(ffi);
					break;
				}
			}

			if (!nbrFound)
			{
				curNbrs.append(curSlave);
				curFaceFaces.append(SLList<label>(ffi));

				// New coarse face created
				nCoarseFaces++;
			}
		}
		else
		{
			// This master has got no neighbours yet.  Add a neighbour
			// and a coefficient, thus creating a new face
			neighboursTable.insert(curMaster, SLList<label>(curSlave));
			faceFaceTable.insert
			(
				curMaster,
				SLList<SLList<label> >(SLList<label>(ffi))
			);

			// New coarse face created
			nCoarseFaces++;
		}
	} // end for all fine faces


	faceCells_.setSize(2 * nCoarseFaces, -1);
	fineAddressing_.setSize(localRestrictAddressing.size(), -1);
	restrictAddressing_.setSize(localRestrictAddressing.size(), -1);

	// All weights are equal to 1: integral matching
	restrictWeights_.setSize(localRestrictAddressing.size(), 1.0);

	labelList contents = neighboursTable.toc();

	// Reset face counter for re-use
	nCoarseFaces = 0;

	// On master side, the owner addressing is stored in table of contents
	forAll(contents, masterI)
	{
		SLList<label>& curNbrs = neighboursTable.find(contents[masterI])();

		SLList<SLList<label> >& curFaceFaces =
			faceFaceTable.find(contents[masterI])();

		SLList<label>::iterator nbrsIter = curNbrs.begin();
		SLList<SLList<label> >::iterator faceFacesIter = curFaceFaces.begin();

		for
			(
				;
				nbrsIter != curNbrs.end(), faceFacesIter != curFaceFaces.end();
				++nbrsIter, ++faceFacesIter
				)
		{
			faceCells_[nCoarseFaces] = contents[masterI];

			for
				(
					SLList<label>::iterator facesIter = faceFacesIter().begin();
					facesIter != faceFacesIter().end();
					++facesIter
					)
			{
				fineAddressing_[facesIter()] = facesIter();
				restrictAddressing_[facesIter()] = nCoarseFaces;
			}

			nCoarseFaces++;
		}
	}

	// On slave side, the owner addressing is stored in linked lists
	forAll(contents, masterI)
	{
		SLList<label>& curNbrs = neighboursTable.find(contents[masterI])();

		SLList<SLList<label> >& curFaceFaces =
			faceFaceTable.find(contents[masterI])();

		SLList<label>::iterator nbrsIter = curNbrs.begin();
		SLList<SLList<label> >::iterator faceFacesIter = curFaceFaces.begin();

		for
			(
				;
				nbrsIter != curNbrs.end(), faceFacesIter != curFaceFaces.end();
				++nbrsIter, ++faceFacesIter
				)
		{
			faceCells_[nCoarseFaces] = nbrsIter();

			for
				(
					SLList<label>::iterator facesIter = faceFacesIter().begin();
					facesIter != faceFacesIter().end();
					++facesIter
					)
			{
				fineAddressing_[facesIter() + sizeBy2] = facesIter() + sizeBy2;
				restrictAddressing_[facesIter() + sizeBy2] = nCoarseFaces;
			}

			nCoarseFaces++;
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::cyclicAMGInterface::~cyclicAMGInterface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::labelField> tnbLib::cyclicAMGInterface::transfer
(
	const Pstream::commsTypes,
	const unallocLabelList& interfaceData
) const
{
	tmp<labelField> tpnf(new labelField(size()));
	labelField& pnf = tpnf();

	label sizeby2 = size() / 2;

	for (label facei = 0; facei < sizeby2; facei++)
	{
		pnf[facei] = interfaceData[facei + sizeby2];
		pnf[facei + sizeby2] = interfaceData[facei];
	}

	return tpnf;
}


tnbLib::tmp<tnbLib::labelField> tnbLib::cyclicAMGInterface::internalFieldTransfer
(
	const Pstream::commsTypes,
	const unallocLabelList& iF
) const
{
	tmp<labelField> tpnf(new labelField(size()));
	labelField& pnf = tpnf();

	label sizeby2 = size() / 2;

	for (label facei = 0; facei < sizeby2; facei++)
	{
		pnf[facei] = iF[faceCells_[facei + sizeby2]];
		pnf[facei + sizeby2] = iF[faceCells_[facei]];
	}

	return tpnf;
}


// ************************************************************************* //