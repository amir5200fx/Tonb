#include <Marine_Section_Sail.hxx>

#include <Marine_SectTools.hxx>
#include <Pln_Wire.hxx>

void tnbLib::marineLib::Section_Sail::CheckCurves() const
{
	Debug_Null_Pointer(Wire());
	const auto& curves = Wire()->RetrieveCurves();
	for (const auto& x : curves)
	{
		if (NOT Marine_SectTools::IsSail(x))
		{
			FatalErrorIn(FunctionSIG)
				<< " the curve is supposed to be a sail!" << endl
				<< abort(FatalError);
		}
	}
}