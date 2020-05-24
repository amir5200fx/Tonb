#include <constTransport.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class thermo>
	constTransport<thermo>::constTransport(Istream& is)
		:
		thermo(is),
		Mu(readScalar(is)),
		rPr(1.0 / readScalar(is))
	{
		is.check("constTransport::constTransport(Istream& is)");
	}


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	template<class thermo>
	Ostream& operator<<(Ostream& os, const constTransport<thermo>& ct)
	{
		operator<<(os, static_cast<const thermo&>(ct));
		os << tab << ct.Mu << tab << 1.0 / ct.rPr;

		os.check("Ostream& operator<<(Ostream& os, const constTransport& ct)");

		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //