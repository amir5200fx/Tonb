#include <ShapePx_ContinProfile.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::ShapePx_ContinProfile::CheckBoundary
(
	const Standard_Real x,
	const char * funcName
) const
{
	if (NOT INSIDE(x, Lower(), Upper()))
	{
		FatalErrorIn(funcName) << endl
			<< "the value is not inside the boundary!" << endl
			<< " - lower: " << Lower() << endl
			<< " - upper: " << Upper() << endl
			<< " - x = " << x << endl
			<< abort(FatalError);
	}
}