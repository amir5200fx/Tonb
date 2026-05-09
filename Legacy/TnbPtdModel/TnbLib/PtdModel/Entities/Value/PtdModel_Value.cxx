#include <PtdModel_Value.hxx>

void tnbLib::PtdModel_Value::SetValue(const Standard_Real x)
{
	theValue_ = x;
	if (NOT IsSpecified_)
	{
		IsSpecified_ = Standard_True;
	}
}