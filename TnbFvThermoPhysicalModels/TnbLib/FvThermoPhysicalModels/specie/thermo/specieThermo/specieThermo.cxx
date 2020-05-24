#include <specieThermo.hxx>

#include <IOstreams.hxx>

/* * * * * * * * * * * * * * * Private Static Data * * * * * * * * * * * * * */

template<class thermo>
const tnbLib::debug::tolerancesSwitch
tnbLib::specieThermo<thermo>::tol_
(
	"speciesThermoTol",
	1e-4
);


template<class thermo>
const tnbLib::debug::tolerancesSwitch
tnbLib::specieThermo<thermo>::TJump_
(
	"speciesThermoTJump",
	20
);


template<class thermo>
const tnbLib::debug::optimisationSwitch
tnbLib::specieThermo<thermo>::maxIter_
(
	"speciesThermoMaxIter",
	100
);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class thermo>
tnbLib::specieThermo<thermo>::specieThermo(Istream& is)
	:
	thermo(is)
{
	is.check("specieThermo::specieThermo(Istream& is)");
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class thermo>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const specieThermo<thermo>& st)
{
	os << static_cast<const thermo&>(st);

	os.check("Ostream& operator<<(Ostream& os, const specieThermo& st)");
	return os;
}


// ************************************************************************* //