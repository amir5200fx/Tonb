#include <pointPatchMapper.hxx>

#include <pointPatch.hxx>
#include <mapPolyMesh.hxx>
#include <faceMapper.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::pointPatchMapper::calcAddressing() const
{
	if
		(
			directAddrPtr_
			|| interpolationAddrPtr_
			|| weightsPtr_
			)
	{
		FatalErrorIn
		(
			"void pointPatchMapper::calcAddressing() const"
		) << "Addressing already calculated"
			<< abort(FatalError);
	}

	if (direct())
	{
		// Direct mapping.
		directAddrPtr_ = new labelList(mpm_.patchPointMap()[patch_.index()]);
		labelList& addr = *directAddrPtr_;

		forAll(addr, i)
		{
			if (addr[i] < 0)
			{
				addr[i] = 0;
			}
		}
	}
	else
	{
		// Interpolative mapping.

		// NOTE: Incorrect:
		// FOR NOW only takes first patch point instead of averaging all
		// patch points. Problem is we don't know what points were in the patch
		// for points that were merged.

		interpolationAddrPtr_ = new labelListList(size());
		labelListList& addr = *interpolationAddrPtr_;

		weightsPtr_ = new scalarListList(addr.size());
		scalarListList& w = *weightsPtr_;

		const labelList& ppm = mpm_.patchPointMap()[patch_.index()];

		forAll(ppm, i)
		{
			if (ppm[i] >= 0)
			{
				addr[i] = labelList(1, ppm[i]);
				w[i] = scalarList(1, 1.0);
			}
			else
			{
				// Inserted point. Map from point0 (arbitrary choice)
				addr[i] = labelList(1, 0);
				w[i] = scalarList(1, 1.0);
			}
		}
	}
}


void tnbLib::pointPatchMapper::clearOut()
{
	deleteDemandDrivenData(directAddrPtr_);
	deleteDemandDrivenData(interpolationAddrPtr_);
	deleteDemandDrivenData(weightsPtr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::pointPatchMapper::pointPatchMapper
(
	const pointPatch& patch,
	const pointMapper& pointMap,
	const mapPolyMesh& mpm
)
	:
	PointPatchFieldMapper(),
	patch_(patch),
	pointMapper_(pointMap),
	mpm_(mpm),
	sizeBeforeMapping_
	(
		patch_.index() < mpm_.oldPatchNMeshPoints().size()
		? mpm_.oldPatchNMeshPoints()[patch_.index()]
		: 0
	),
	directAddrPtr_(NULL),
	interpolationAddrPtr_(NULL),
	weightsPtr_(NULL)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pointPatchMapper::~pointPatchMapper()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::unallocLabelList& tnbLib::pointPatchMapper::directAddressing() const
{
	if (!direct())
	{
		FatalErrorIn
		(
			"const unallocLabelList& pointPatchMapper::directAddressing() const"
		) << "Requested direct addressing for an interpolative mapper."
			<< abort(FatalError);
	}

	if (!directAddrPtr_)
	{
		calcAddressing();
	}

	return *directAddrPtr_;
}


const tnbLib::labelListList& tnbLib::pointPatchMapper::addressing() const
{
	if (direct())
	{
		FatalErrorIn
		(
			"const labelListList& pointPatchMapper::addressing() const"
		) << "Requested interpolative addressing for a direct mapper."
			<< abort(FatalError);
	}

	if (!interpolationAddrPtr_)
	{
		calcAddressing();
	}

	return *interpolationAddrPtr_;
}


const tnbLib::scalarListList& tnbLib::pointPatchMapper::weights() const
{
	if (direct())
	{
		FatalErrorIn
		(
			"const scalarListList& pointPatchMapper::weights() const"
		) << "Requested interpolative weights for a direct mapper."
			<< abort(FatalError);
	}

	if (!weightsPtr_)
	{
		calcAddressing();
	}

	return *weightsPtr_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


// ************************************************************************* //