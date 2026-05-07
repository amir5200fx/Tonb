#include <Model_UniformParamProfile.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::Model_UniformParamProfile::Value
(
	const Standard_Real x
) const
{
	if (NOT InsideSpan(x))
	{
		FatalErrorIn(FunctionSIG)
			<< " the parameter is outside the span." << endl
			<< " - x: " << x << endl
			<< " - lower: " << Lower() << endl
			<< " - upper: " << Upper() << endl
			<< abort(FatalError);
	}
	return theValue_;
}