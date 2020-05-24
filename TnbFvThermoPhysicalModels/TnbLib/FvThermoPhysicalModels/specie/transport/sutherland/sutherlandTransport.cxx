#include <sutherlandTransport.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class thermo>
	sutherlandTransport<thermo>::sutherlandTransport(Istream& is)
		:
		thermo(is),
		As(readScalar(is)),
		Ts(readScalar(is))
	{
		is.check("sutherlandTransport<thermo>::sutherlandTransport(Istream&)");
	}


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	template<class thermo>
	Ostream& operator<<(Ostream& os, const sutherlandTransport<thermo>& st)
	{
		os << static_cast<const thermo&>(st) << tab << st.As << tab << st.Ts;

		os.check
		(
			"Ostream& operator<<(Ostream&, const sutherlandTransport<thermo>&)"
		);

		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //