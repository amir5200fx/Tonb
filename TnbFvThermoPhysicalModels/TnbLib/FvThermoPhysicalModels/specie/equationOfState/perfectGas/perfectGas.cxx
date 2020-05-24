#include <perfectGas.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	perfectGas::perfectGas(Istream& is)
		:
		specie(is)
	{
		is.check("perfectGas::perfectGas(Istream& is)");
	}


	// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

	Ostream& operator<<(Ostream& os, const perfectGas& pg)
	{
		os << static_cast<const specie&>(pg);

		os.check("Ostream& operator<<(Ostream& os, const perfectGas& st)");
		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //