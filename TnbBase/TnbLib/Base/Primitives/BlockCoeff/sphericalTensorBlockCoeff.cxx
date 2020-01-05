#include <sphericalTensorBlockCoeff.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::BlockCoeff<tnbLib::sphericalTensor>::BlockCoeff()
	:
	DecoupledBlockCoeff<sphericalTensor>()
{}


tnbLib::BlockCoeff<tnbLib::sphericalTensor>::BlockCoeff
(
	const BlockCoeff<sphericalTensor>& f
)
	:
	DecoupledBlockCoeff<sphericalTensor>(f)
{}


tnbLib::BlockCoeff<tnbLib::sphericalTensor>::BlockCoeff(Istream& is)
	:
	DecoupledBlockCoeff<sphericalTensor>(is)
{}


// ************************************************************************* //