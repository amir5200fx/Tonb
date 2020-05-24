#include <hPolynomialThermo.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
tnbLib::hPolynomialThermo<EquationOfState, PolySize>::hPolynomialThermo
(
	Istream& is
)
	:
	EquationOfState(is),
	Hf_(readScalar(is)),
	Sf_(readScalar(is)),
	cpPolynomial_("cpPolynomial", is),
	hPolynomial_(),
	sPolynomial_()
{
	Hf_ *= this->W();
	Sf_ *= this->W();
	cpPolynomial_ *= this->W();

	hPolynomial_ = cpPolynomial_.integrate();
	sPolynomial_ = cpPolynomial_.integrateMinus1();

	// Offset h poly so that it is relative to the enthalpy at Tstd
	hPolynomial_[0] += Hf_ - hPolynomial_.evaluate(specie::Tstd());

	// Offset s poly so that it is relative to the entropy at Tstd
	sPolynomial_[0] += Sf_ - sPolynomial_.evaluate(specie::Tstd());
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const hPolynomialThermo<EquationOfState, PolySize>& pt
	)
{
	os << static_cast<const EquationOfState&>(pt) << tab
		<< pt.Hf_ / pt.W() << tab
		<< pt.Sf_ << tab
		<< "cpPolynomial" << tab << pt.cpPolynomial_ / pt.W();

	os.check
	(
		"operator<<"
		"("
		"Ostream&, "
		"const hPolynomialThermo<EquationOfState, PolySize>&"
		")"
	);

	return os;
}


// ************************************************************************* //