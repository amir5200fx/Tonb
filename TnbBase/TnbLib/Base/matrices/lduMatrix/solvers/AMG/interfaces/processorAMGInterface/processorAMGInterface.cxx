#include <processorAMGInterface.hxx>

#include <Hash.hxx>
#include <SLList.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(processorAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		AMGInterface,
		processorAMGInterface,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::processorAMGInterface::processorAMGInterface
(
	const lduPrimitiveMesh& lduMesh,
	const lduInterface& fineInterface,
	const labelField& localRestrictAddressing,
	const labelField& neighbourRestrictAddressing
)
	:
	AMGInterface(lduMesh),
	fineProcInterface_(refCast<const processorLduInterface>(fineInterface))
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

	forAll(localRestrictAddressing, ffi)
	{
		label curMaster = -1;
		label curSlave = -1;

		// Do switching on master/slave indexes based on the owner/neighbour of
		// the processor index such that both sides get the same answer.
		if (myProcNo() < neighbProcNo())
		{
			// Master side
			curMaster = localRestrictAddressing[ffi];
			curSlave = neighbourRestrictAddressing[ffi];
		}
		else
		{
			// Slave side
			curMaster = neighbourRestrictAddressing[ffi];
			curSlave = localRestrictAddressing[ffi];
		}

		// Look for the master cell.  If it has already got a face,
		// add the coefficient to the face.  If not, create a new face.
		if (neighboursTable.found(curMaster))
		{
			// Check all current neighbours to see if the current slave already
			// exists and if so, add the fine face to the agglomeration.

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


	faceCells_.setSize(nCoarseFaces, -1);
	fineAddressing_.setSize(localRestrictAddressing.size(), -1);
	restrictAddressing_.setSize(localRestrictAddressing.size(), -1);

	// All weights are equal to 1: integral matching
	restrictWeights_.setSize(localRestrictAddressing.size(), 1.0);

	labelList contents = neighboursTable.toc();

	// Sort makes sure the order is identical on both sides.
	// HJ, 20/Feb.2009
	sort(contents);

	// Reset face counter for re-use
	nCoarseFaces = 0;

	if (myProcNo() < neighbProcNo())
	{
		// On master side, the owner addressing is stored in table of contents
		forAll(contents, masterI)
		{
			SLList<label>& curNbrs = neighboursTable.find(contents[masterI])();

			SLList<SLList<label> >& curFaceFaces =
				faceFaceTable.find(contents[masterI])();

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
	}
	else
	{
		// On slave side, the owner addressing is stored in linked lists
		forAll(contents, masterI)
		{
			SLList<label>& curNbrs = neighboursTable.find(contents[masterI])();

			SLList<SLList<label> >& curFaceFaces =
				faceFaceTable.find(contents[masterI])();

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
				faceCells_[nCoarseFaces] = nbrsIter();

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
	}
}


// * * * * * * * * * * * * * * * * Desstructor * * * * * * * * * * * * * * * //

tnbLib::processorAMGInterface::~processorAMGInterface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::processorAMGInterface::initTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& interfaceData
) const
{
	send(commsType, interfaceData);
}


tnbLib::tmp<tnbLib::labelField> tnbLib::processorAMGInterface::transfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& interfaceData
) const
{
	return receive<label>(commsType, this->size());
}


void tnbLib::processorAMGInterface::initInternalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& iF
) const
{
	send(commsType, interfaceInternalField(iF)());
}


tnbLib::tmp<tnbLib::labelField> tnbLib::processorAMGInterface::internalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList&
) const
{
	return receive<label>(commsType, this->size());
}


// ************************************************************************* //