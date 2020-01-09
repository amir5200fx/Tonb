#include <mixingPlaneAMGInterface.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mixingPlaneAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		AMGInterface,
		mixingPlaneAMGInterface,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::mixingPlaneAMGInterface::mixingPlaneAMGInterface
(
	const lduPrimitiveMesh& lduMesh,
	const lduInterface& fineInterface,
	const labelField& localRestrictAddressing,
	const labelField& neighbourRestrictAddressing
)
	:
	AMGInterface(lduMesh),
	fineMixingPlaneInterface_
	(
		refCast<const mixingPlaneLduInterface>(fineInterface)
	)
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::mixingPlaneAMGInterface::~mixingPlaneAMGInterface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::mixingPlaneAMGInterface::agglomerateCoeffs
(
	const scalarField& fineCoeffs
) const
{
	// AMG agglomeration missing
	notImplemented("mixingPlaneAMGInterface::agglomerateCoeffs");
	tmp<scalarField> tcoarseCoeffs(new scalarField(size(), 0.0));

	return tcoarseCoeffs;
}


bool tnbLib::mixingPlaneAMGInterface::master() const
{
	return fineMixingPlaneInterface_.master();
}


tnbLib::label tnbLib::mixingPlaneAMGInterface::shadowIndex() const
{
	return fineMixingPlaneInterface_.shadowIndex();
}


const tnbLib::mixingPlaneLduInterface&
tnbLib::mixingPlaneAMGInterface::shadowInterface() const
{
	return refCast<const mixingPlaneLduInterface>
		(
			ldu().interfaces()[shadowIndex()]
			);
}


const tnbLib::labelListList& tnbLib::mixingPlaneAMGInterface::addressing() const
{
	FatalErrorIn
	(
		"const labelListList& mixingPlaneAMGInterface::addressing() const"
	) << "Requested fine addressing at coarse level"
		<< abort(FatalError);

	return labelListList::null();
}


const tnbLib::scalarListList& tnbLib::mixingPlaneAMGInterface::weights() const
{
	FatalErrorIn
	(
		"const labelListList& mixingPlaneAMGInterface::weights() const"
	) << "Requested fine addressing at coarse level"
		<< abort(FatalError);
	return scalarListList::null();
}


const tnbLib::tensorField& tnbLib::mixingPlaneAMGInterface::forwardT() const
{
	return fineMixingPlaneInterface_.forwardT();
}


const tnbLib::tensorField& tnbLib::mixingPlaneAMGInterface::reverseT() const
{
	return fineMixingPlaneInterface_.reverseT();
}


void tnbLib::mixingPlaneAMGInterface::initTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& interfaceData
) const
{
	labelTransferBuffer_ = interfaceData;
}


tnbLib::tmp<tnbLib::labelField> tnbLib::mixingPlaneAMGInterface::transfer
(
	const Pstream::commsTypes,
	const unallocLabelList& interfaceData
) const
{
	return this->shadowInterface().labelTransferBuffer();
}


void tnbLib::mixingPlaneAMGInterface::initInternalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& iF
) const
{
	labelTransferBuffer_ = interfaceInternalField(iF);
}


void tnbLib::mixingPlaneAMGInterface::initInternalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const scalarField& iF
) const
{
	fieldTransferBuffer_ = interfaceInternalField(iF);
}


tnbLib::tmp<tnbLib::labelField>
tnbLib::mixingPlaneAMGInterface::internalFieldTransfer
(
	const Pstream::commsTypes,
	const unallocLabelList&
) const
{
	return shadowInterface().labelTransferBuffer();
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::mixingPlaneAMGInterface::internalFieldTransfer
(
	const Pstream::commsTypes,
	const scalarField&
) const
{
	return shadowInterface().fieldTransferBuffer();
}


// ************************************************************************* //