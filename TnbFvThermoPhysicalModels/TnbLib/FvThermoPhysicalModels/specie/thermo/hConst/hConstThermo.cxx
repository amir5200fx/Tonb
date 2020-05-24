#include <hConstThermo.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class equationOfState>
tnbLib::hConstThermo<equationOfState>::hConstThermo(Istream& is)
	:
	equationOfState(is),
	Cp_(readScalar(is)),
	Hf_(readScalar(is))
{
	is.check("hConstThermo::hConstThermo(Istream& is)");
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class equationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const hConstThermo<equationOfState>& ct
	)
{
	os << static_cast<const equationOfState&>(ct) << tab
		<< ct.Cp_ << tab << ct.Hf_;

	os.check("Ostream& operator<<(Ostream& os, const hConstThermo& ct)");
	return os;
}


// ************************************************************************* //