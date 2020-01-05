#include <tensorBlockCoeff.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::BlockCoeff<tnbLib::tensor>::BlockCoeff()
	:
	DecoupledBlockCoeff<tensor>()
{}


tnbLib::BlockCoeff<tnbLib::tensor>::BlockCoeff(const BlockCoeff<tensor>& f)
	:
	DecoupledBlockCoeff<tensor>(f)
{}


tnbLib::BlockCoeff<tnbLib::tensor>::BlockCoeff(Istream& is)
	:
	DecoupledBlockCoeff<tensor>(is)
{}


// ************************************************************************* //