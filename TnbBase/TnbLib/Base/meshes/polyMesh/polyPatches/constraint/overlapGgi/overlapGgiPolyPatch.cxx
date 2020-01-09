#include <overlapGgiPolyPatch.hxx>

#include <polyBoundaryMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <demandDrivenData.hxx>
#include <polyPatchID.hxx>
#include <ZoneIDs.hxx>
#include <SubField.hxx>
#include <Pstream.hxx>
#include <PstreamReduceOps.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(overlapGgiPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, overlapGgiPolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, overlapGgiPolyPatch, dictionary);
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::overlapGgiPolyPatch::active() const
{
	polyPatchID shadow(shadowName_, boundaryMesh());
	faceZoneID zone(zoneName_, boundaryMesh().mesh().faceZones());

	return shadow.active() && zone.active();
}


void tnbLib::overlapGgiPolyPatch::calcLocalParallel() const
{
	// Calculate patch-to-zone addressing
	if (localParallelPtr_)
	{
		FatalErrorIn("void overlapGgiPolyPatch::calcLocalParallel() const")
			<< "Local parallel switch already calculated"
			<< abort(FatalError);
	}

	// If running in serial, all GGIs are local parallel
	// HJ, 1/Jun/2011
	localParallelPtr_ = new bool(false);
	bool& emptyOrComplete = *localParallelPtr_;

	// If running in serial, all GGIs are expanded to zone size.
	// This happens on decomposition and reconstruction where
	// size and shadow size may be zero, but zone size may not
	// HJ, 1/Jun/2011
	if (!Pstream::parRun())
	{
		emptyOrComplete = false;
	}
	else
	{
		// Check that patch size is greater than the zone size.
		// This is an indication of the error where the face zone is not global
		// in a parallel run.  HJ, 9/Nov/2014
		if (size() > zone().size())
		{
			FatalErrorIn("void overlapGgiPolyPatch::calcLocalParallel() const")
				<< "Patch size is greater than zone size for GGI patch "
				<< name() << ".  This is not allowerd: "
				<< "the face zone must contain all patch faces and be "
				<< "global in parallel runs"
				<< abort(FatalError);
		}

		// Calculate localisation on master and shadow
		emptyOrComplete =
			(
				zone().size() == size()
				&& shadow().zone().size() == shadow().size()
				)
			|| (size() == 0 && shadow().size() == 0);

		reduce(emptyOrComplete, andOp<bool>());
	}

	if (debug && Pstream::parRun())
	{
		Info << "Overlap GGI patch Master: " << name()
			<< " Slave: " << shadowName() << " is ";

		if (emptyOrComplete)
		{
			Info << "local parallel" << endl;
		}
		else
		{
			Info << "split between multiple processors" << endl;
		}
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::overlapGgiPolyPatch::overlapGgiPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm
)
	:
	coupledPolyPatch(name, size, start, index, bm),
	shadowName_(word::null),
	zoneName_(word::null),
	shadowIndex_(-1),
	zoneIndex_(-1),
	rotationAxis_(vector(0, 0, 1)),
	nCopies_(0),
	expandedMasterPtr_(NULL),
	expandedSlavePtr_(NULL),
	patchToPatchPtr_(NULL),
	localParallelPtr_(NULL),
	reconFaceCellCentresPtr_(NULL)
{}


// Construct from components
tnbLib::overlapGgiPolyPatch::overlapGgiPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm,
	const word& shadowName,
	const word& zoneName,
	const vector& axis,
	const scalar nCopies
)
	:
	coupledPolyPatch(name, size, start, index, bm),
	shadowName_(shadowName),
	zoneName_(zoneName),
	shadowIndex_(-1),
	zoneIndex_(-1),
	rotationAxis_(axis),
	nCopies_(nCopies),
	expandedMasterPtr_(NULL),
	expandedSlavePtr_(NULL),
	patchToPatchPtr_(NULL),
	localParallelPtr_(NULL),
	reconFaceCellCentresPtr_(NULL)
{}


// Construct from dictionary
tnbLib::overlapGgiPolyPatch::overlapGgiPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm
)
	:
	coupledPolyPatch(name, dict, index, bm),
	shadowName_(dict.lookup("shadowPatch")),
	zoneName_(dict.lookup("zone")),
	shadowIndex_(-1),
	zoneIndex_(-1),
	rotationAxis_(dict.lookup("rotationAxis")),
	nCopies_(readScalar(dict.lookup("nCopies"))),
	expandedMasterPtr_(NULL),
	expandedSlavePtr_(NULL),
	patchToPatchPtr_(NULL),
	localParallelPtr_(NULL),
	reconFaceCellCentresPtr_(NULL)
{}


//- Construct as copy, resetting the boundary mesh
tnbLib::overlapGgiPolyPatch::overlapGgiPolyPatch
(
	const overlapGgiPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	coupledPolyPatch(pp, bm),
	shadowName_(pp.shadowName_),
	zoneName_(pp.zoneName_),
	shadowIndex_(-1),
	zoneIndex_(-1),
	rotationAxis_(pp.rotationAxis_),
	nCopies_(pp.nCopies_),
	expandedMasterPtr_(NULL),
	expandedSlavePtr_(NULL),
	patchToPatchPtr_(NULL),
	localParallelPtr_(NULL),
	reconFaceCellCentresPtr_(NULL)
{}


//- Construct as copy, resetting the face list and boundary mesh data
tnbLib::overlapGgiPolyPatch::overlapGgiPolyPatch
(
	const overlapGgiPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	coupledPolyPatch(pp, bm, index, newSize, newStart),
	shadowName_(pp.shadowName_),
	zoneName_(pp.zoneName_),
	shadowIndex_(-1),
	zoneIndex_(-1),
	rotationAxis_(pp.rotationAxis_),
	nCopies_(pp.nCopies_),
	expandedMasterPtr_(NULL),
	expandedSlavePtr_(NULL),
	patchToPatchPtr_(NULL),
	localParallelPtr_(NULL),
	reconFaceCellCentresPtr_(NULL)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::overlapGgiPolyPatch::~overlapGgiPolyPatch()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::overlapGgiPolyPatch::shadowIndex() const
{
	if (shadowIndex_ == -1 && shadowName_ != word::null)
	{
		// Grab shadow patch index
		polyPatchID shadow(shadowName_, boundaryMesh());

		if (!shadow.active())
		{
			FatalErrorIn("label overlapGgiPolyPatch::shadowIndex() const")
				<< "Shadow patch name " << shadowName_
				<< " not found.  Please check your GGI interface definition."
				<< abort(FatalError);
		}

		shadowIndex_ = shadow.index();

		// Check the other side is a ggi
		if (!isA<overlapGgiPolyPatch>(boundaryMesh()[shadowIndex_]))
		{
			FatalErrorIn("label overlapGgiPolyPatch::shadowIndex() const")
				<< "Shadow of ggi patch " << name()
				<< " named " << shadowName() << " is not a ggi.  Type: "
				<< boundaryMesh()[shadowIndex_].type() << nl
				<< "This is not allowed.  Please check your mesh definition."
				<< abort(FatalError);
		}

		if (index() == shadowIndex_)
		{
			FatalErrorIn("label overlapGgiPolyPatch::shadowIndex() const")
				<< "ggi patch " << name() << " created as its own shadow"
				<< abort(FatalError);
		}
	}

	return shadowIndex_;
}

tnbLib::label tnbLib::overlapGgiPolyPatch::zoneIndex() const
{
	if (zoneIndex_ == -1 && zoneName_ != tnbLib::word::null)
	{
		// Grab zone patch index
		faceZoneID zone(zoneName_, boundaryMesh().mesh().faceZones());

		if (!zone.active())
		{
			FatalErrorIn("label overlapGgiPolyPatch::zoneIndex() const")
				<< "Face zone name " << zoneName_
				<< " not found.  Please check your GGI interface definition."
				<< abort(FatalError);
		}

		zoneIndex_ = zone.index();
	}

	return zoneIndex_;
}

const tnbLib::overlapGgiPolyPatch&
tnbLib::overlapGgiPolyPatch::shadow() const
{
	return refCast<const overlapGgiPolyPatch>(boundaryMesh()[shadowIndex()]);
}


const tnbLib::faceZone& tnbLib::overlapGgiPolyPatch::zone() const
{
	return boundaryMesh().mesh().faceZones()[zoneIndex()];
}


bool tnbLib::overlapGgiPolyPatch::localParallel() const
{
	// Calculate patch-to-zone addressing
	if (!localParallelPtr_)
	{
		calcLocalParallel();
	}

	return *localParallelPtr_;
}


const tnbLib::label& tnbLib::overlapGgiPolyPatch::nCopies() const
{
	// Read the number of copies to be made from the dictionary for the
	// expanded slave and expanded master to cover 360 degrees
	return nCopies_;
}


bool tnbLib::overlapGgiPolyPatch::master() const
{
	// The first overlapggi interface is master,second one is slave
	if (angle() == shadow().angle())
	{
		return index() < shadowIndex();
	}

	// Master is the one with the larger angle
	return angle() > shadow().angle();
}


// Write
void tnbLib::overlapGgiPolyPatch::write(Ostream& os) const
{
	polyPatch::write(os);
	os.writeKeyword("rotationAxis") << rotationAxis_
		<< token::END_STATEMENT << nl;
	os.writeKeyword("nCopies") << nCopies_
		<< token::END_STATEMENT << nl;
	os.writeKeyword("shadowPatch") << shadowName_
		<< token::END_STATEMENT << nl;
	os.writeKeyword("zone") << zoneName_
		<< token::END_STATEMENT << nl;
}


// ************************************************************************* //