#include <icoPolynomial.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<int PolySize>
	icoPolynomial<PolySize>::icoPolynomial(Istream& is)
		:
		specie(is),
		rhoPolynomial_("rhoPolynomial", is)
	{
		rhoPolynomial_ *= this->W();
	}


	// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

	template<int PolySize>
	Ostream& operator<<(Ostream& os, const icoPolynomial<PolySize>& ip)
	{
		os << static_cast<const specie&>(ip) << tab
			<< "rhoPolynomial" << tab << ip.rhoPolynomial_ / ip.W();

		os.check
		(
			"Ostream& operator<<(Ostream& os, const icoPolynomial<PolySize>& ip)"
		);

		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //