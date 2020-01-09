#include <procLduInterface.hxx>

#include <lduInterfaceField.hxx>
#include <cyclicLduInterface.hxx>
#include <processorLduInterface.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::procLduInterface::procLduInterface
(
	const lduInterfaceField& interface,
	const scalarField& coeffs
)
	:
	faceCells_(interface.coupledInterface().faceCells()),
	coeffs_(coeffs),
	myProcNo_(-1),
	neighbProcNo_(-1)
{
	if (isA<processorLduInterface>(interface.coupledInterface()))
	{
		const processorLduInterface& pldui =
			refCast<const processorLduInterface>(interface.coupledInterface());

		myProcNo_ = pldui.myProcNo();
		neighbProcNo_ = pldui.neighbProcNo();
	}
	else if (isA<cyclicLduInterface>(interface.coupledInterface()))
	{
	}
	else
	{
		FatalErrorIn
		(
			"procLduInterface::procLduInterface"
			"(const lduInterfaceField&, const scalarField&"
		) << "unknown lduInterface type "
			<< interface.coupledInterface().type()
			<< exit(FatalError);
	}
}


tnbLib::procLduInterface::procLduInterface(Istream& is)
	:
	faceCells_(is),
	coeffs_(is),
	myProcNo_(readLabel(is)),
	neighbProcNo_(readLabel(is))
{}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const procLduInterface& cldui)
{
	os << cldui.faceCells_
		<< cldui.coeffs_
		<< cldui.myProcNo_
		<< cldui.neighbProcNo_;

	return os;
}


// ************************************************************************* //