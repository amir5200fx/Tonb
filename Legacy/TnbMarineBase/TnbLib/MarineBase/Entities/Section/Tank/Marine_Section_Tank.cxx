#include <Marine_Section_Tank.hxx>

#include <Marine_SectTools.hxx>
#include <Pln_Wire.hxx>

void tnbLib::marineLib::Section_Tank::CheckCurves() const
{
	Debug_Null_Pointer(Wire());
	const auto& curves = Wire()->RetrieveCurves();
	for (const auto& x : curves)
	{
		if (NOT Marine_SectTools::IsTank(x))
		{
			FatalErrorIn(FunctionSIG)
				<< " the curve is supposed to be a tank!" << endl
				<< abort(FatalError);
		}
	}
}