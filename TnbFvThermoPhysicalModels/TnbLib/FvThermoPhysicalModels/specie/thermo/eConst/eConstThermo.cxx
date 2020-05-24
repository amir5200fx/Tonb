#include <eConstThermo.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class equationOfState>
tnbLib::eConstThermo<equationOfState>::eConstThermo(Istream& is)
	:
	equationOfState(is),
	Cv_(readScalar(is)),
	Hf_(readScalar(is))
{
	is.check("eConstThermo::eConstThermo(Istream& is)");
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class equationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const eConstThermo<equationOfState>& ct
	)
{
	os << static_cast<const equationOfState&>(ct) << tab
		<< ct.Cv_ << tab << ct.Hf_;

	os.check("Ostream& operator<<(Ostream& os, const eConstThermo& ct)");
	return os;
}


// ************************************************************************* //