#include <FadOne.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<int nVars>
	const char* const FadOne<nVars>::typeName = "FadOne";

	template<int nVars>
	const FadOne<nVars> FadOne<nVars>::zero = FadOne<nVars>(0);

	template<int nVars>
	const FadOne<nVars> FadOne<nVars>::one = FadOne<nVars>(1);


	


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //