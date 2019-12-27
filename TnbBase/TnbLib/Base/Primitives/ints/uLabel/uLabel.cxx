#include <uLabel.hxx>

#include <error.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const char* const pTraits<uLabel>::typeName = "uLabel";
	const uLabel pTraits<uLabel>::zero = 0;
	const uLabel pTraits<uLabel>::one = 1;
	const uLabel pTraits<uLabel>::min = uLabelMin;
	const uLabel pTraits<uLabel>::max = uLabelMax;

	const char* pTraits<uLabel>::componentNames[] = { "x" };

	pTraits<uLabel>::pTraits(Istream& is)
	{
		is >> p_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //