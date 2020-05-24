#include <polynomialTransport.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
tnbLib::polynomialTransport<Thermo, PolySize>::polynomialTransport(Istream& is)
	:
	Thermo(is),
	muPolynomial_("muPolynomial", is),
	kappaPolynomial_("kappaPolynomial", is)
{
	muPolynomial_ *= this->W();
	kappaPolynomial_ *= this->W();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Thermo, int PolySize>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const polynomialTransport<Thermo, PolySize>& pt
	)
{
	os << static_cast<const Thermo&>(pt) << tab
		<< "muPolynomial" << tab << pt.muPolynomial_ / pt.W() << tab
		<< "kappaPolynomial" << tab << pt.kappaPolynomial_ / pt.W();

	os.check
	(
		"Ostream& operator<<"
		"("
		"Ostream&, "
		"const polynomialTransport<Thermo, PolySize>&"
		")"
	);

	return os;
}


// ************************************************************************* //