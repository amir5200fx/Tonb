#include <Marine_Section_Displacer.hxx>

#include <Marine_SectTools.hxx>
#include <Pln_Wire.hxx>

void tnbLib::marineLib::Section_Displacer::CheckCurves() const
{
	Debug_Null_Pointer(Wire());
	const auto& curves = Wire()->RetrieveCurves();
	for (const auto& x : curves)
	{
		if (NOT Marine_SectTools::IsDisplacer(x))
		{
			FatalErrorIn(FunctionSIG)
				<< " the curve is supposed to be a displacer!" << endl
				<< abort(FatalError);
		}
	}
}