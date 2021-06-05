#include <PtdModel_BndValue.hxx>

void tnbLib::PtdModel_BndValue::SetValue(const Standard_Real x)
{
	if (NOT IsInside(x))
	{
		FatalErrorIn(FunctionSIG)
			<< "the value is exceeded the boundaries" << endl
			<< " - lower: " << Lower() << endl
			<< " - upper:" << Upper() << endl
			<< " - value: " << x << endl
			<< abort(FatalError);
	}
	PtdModel_Value::SetValue(x);
}