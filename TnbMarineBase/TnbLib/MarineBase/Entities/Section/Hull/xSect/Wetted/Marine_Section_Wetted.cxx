#include <Marine_Section_Wetted.hxx>

#include <Pln_Wire.hxx>
#include <Marine_PlnCurve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::marineLib::Section_Wetted::RetrieveCurvesOnWater() const
{
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	RetrieveCurvesOnWaterTo(curves);

	return std::move(curves);
}

void tnbLib::marineLib::Section_Wetted::RetrieveCurvesOnWaterTo
(
	std::vector<std::shared_ptr<Pln_Curve>>& theCurves
) const
{
	if (NOT Wire())
	{
		FatalErrorIn("void RetrieveCurvesOnWaterTo(std::vector<std::shared_ptr<Pln_Curve>>& theCurves) const")
			<< "the section has no wire!" << endl
			<< abort(FatalError);
	}

	for (const auto& x : Wire()->RetrieveCurves())
	{
		Debug_Null_Pointer(x);
		if (x->IsMarine())
		{
			auto mCurve = std::dynamic_pointer_cast<Marine_PlnCurve>(x);
			Debug_Null_Pointer(mCurve);

			if (mCurve->IsOnWater())
			{
				theCurves.push_back(x);
			}
		}
	}
}