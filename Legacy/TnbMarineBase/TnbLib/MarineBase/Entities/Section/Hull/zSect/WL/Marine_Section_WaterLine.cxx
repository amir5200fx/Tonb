#include <Marine_Section_WaterLine.hxx>

#include <Marine_SectTools.hxx>
#include <Pln_Wire.hxx>

void tnbLib::marineLib::Section_WaterLine::CheckCurves() const
{
	Debug_Null_Pointer(Wire());
	const auto& curves = Wire()->RetrieveCurves();
	for (const auto& x : curves)
	{
		if (NOT Marine_SectTools::IsWaterLine(x))
		{
			FatalErrorIn(FunctionSIG)
				<< " the curve is supposed to be a water-line!" << endl
				<< abort(FatalError);
		}
	}
}