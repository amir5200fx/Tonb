#include <specie.hxx>

#include <IOstreams.hxx>
#include <dimensionedConstants.hxx>

/* * * * * * * * * * * * * public constants  * * * * * * * * * * * * */

//- Universal gas constant (default in [J/(kmol K)])
const tnbLib::debug::constantsSwitch
tnbLib::specie::RR
(
	"R",
	8314.51,
	"Universal gas constant [J/(kmol K)]"
);


//- Standard pressure (default in [Pa])
const tnbLib::debug::constantsSwitch
tnbLib::specie::Pstd
(
	"Pstd",
	1.0e5,
	"Standard pressure [Pa]"
);

//- Standard temperature (default in [K])
const tnbLib::debug::constantsSwitch
tnbLib::specie::Tstd
(
	"Tstd",
	298.15,
	"Standard temperature [K]"
);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::specie::specie(Istream& is)
	:
	name_(is),
	nMoles_(readScalar(is)),
	molWeight_(readScalar(is))
{
	is.check("specie::specie(Istream& is)");
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const specie& st)
{
	os << st.name_ << tab
		<< st.nMoles_ << tab
		<< st.molWeight_;

	os.check("Ostream& operator<<(Ostream& os, const specie& st)");
	return os;
}


// ************************************************************************* //