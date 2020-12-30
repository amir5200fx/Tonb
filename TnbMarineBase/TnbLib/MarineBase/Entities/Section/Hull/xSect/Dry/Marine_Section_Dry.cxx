#include <Marine_Section_Dry.hxx>

#include <Marine_SectTools.hxx>
#include <Pln_Wire.hxx>

void tnbLib::marineLib::Section_Dry::CheckCurves() const
{
	Debug_Null_Pointer(Wire());
	const auto& curves = Wire()->RetrieveCurves();
	for (const auto& x : curves)
	{
		if (NOT (Marine_SectTools::IsDry(x) OR Marine_SectTools::IsWater(x)))
		{
			FatalErrorIn(FunctionSIG)
				<< " the curve is supposed to be a dry!" << endl
				<< abort(FatalError);
		}
	}
}