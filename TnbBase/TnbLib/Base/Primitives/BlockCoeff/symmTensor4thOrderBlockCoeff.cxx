#include <symmTensor4thOrderBlockCoeff.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::BlockCoeff<tnbLib::symmTensor4thOrder>::BlockCoeff()
	:
	DecoupledBlockCoeff<symmTensor4thOrder>()
{}


tnbLib::BlockCoeff<tnbLib::symmTensor4thOrder>::BlockCoeff
(
	const BlockCoeff<symmTensor4thOrder>& f
)
	:
	DecoupledBlockCoeff<symmTensor4thOrder>(f)
{}


tnbLib::BlockCoeff<tnbLib::symmTensor4thOrder>::BlockCoeff(Istream& is)
	:
	DecoupledBlockCoeff<symmTensor4thOrder>(is)
{}


// ************************************************************************* //