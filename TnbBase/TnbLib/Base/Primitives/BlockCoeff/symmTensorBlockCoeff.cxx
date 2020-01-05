#include <symmTensorBlockCoeff.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::BlockCoeff<tnbLib::symmTensor>::BlockCoeff()
	:
	DecoupledBlockCoeff<symmTensor>()
{}


tnbLib::BlockCoeff<tnbLib::symmTensor>::BlockCoeff
(
	const BlockCoeff<symmTensor>& f
)
	:
	DecoupledBlockCoeff<symmTensor>(f)
{}


tnbLib::BlockCoeff<tnbLib::symmTensor>::BlockCoeff(Istream& is)
	:
	DecoupledBlockCoeff<symmTensor>(is)
{}


// ************************************************************************* //