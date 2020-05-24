#include <realGasSpecieThermo.hxx>

#include <IOstreams.hxx>

/* * * * * * * * * * * * * * * Private Static Data * * * * * * * * * * * * * */

template<class thermo>
const tnbLib::debug::tolerancesSwitch
tnbLib::realGasSpecieThermo<thermo>::tol_
(
	"realGasSpecieThermoTol",
	1.0e-9
);

template<class thermo>
const tnbLib::debug::optimisationSwitch
tnbLib::realGasSpecieThermo<thermo>::maxIter_
(
	"realGasSpecieThermoMaxIter",
	500
);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class thermo>
tnbLib::realGasSpecieThermo<thermo>::realGasSpecieThermo(Istream& is)
	:
	thermo(is)
{
	is.check("realGasSpecieThermo::realGasSpecieThermo(Istream& is)");
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class thermo>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const realGasSpecieThermo<thermo>& st)
{
	os << static_cast<const thermo&>(st);

	os.check("Ostream& operator<<(Ostream& os, const realGasSpecieThermo& st)");
	return os;
}


// ************************************************************************* //