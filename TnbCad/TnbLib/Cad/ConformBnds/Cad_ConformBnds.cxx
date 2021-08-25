#include <Cad_ConformBnds.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Cad_ConformBnds::Perform()
{
	if (NOT Solid())
	{
		FatalErrorIn(FunctionSIG)
			<< "no solid model has been loaded!" << endl
			<< abort(FatalError);
	}


}