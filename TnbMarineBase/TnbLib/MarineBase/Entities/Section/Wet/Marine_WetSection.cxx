#include <Marine_WetSection.hxx>

#include <Pln_Wire.hxx>
#include <Marine_WaterCurve.hxx>
#include <Marine_PlnCurve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::Marine_WetSection::Marine_WetSection
(
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Section(theWire)
	, IsDeep_(Standard_False)
{
}

tnbLib::Marine_WetSection::Marine_WetSection
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Section(theIndex, theWire)
	, IsDeep_(Standard_False)
{
}

tnbLib::Marine_WetSection::Marine_WetSection
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Section(theIndex, theName, theWire)
	, IsDeep_(Standard_False)
{
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::Marine_WetSection::RetrieveCurvesOnWater() const
{
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	RetrieveCurvesOnWaterTo(curves);

	return std::move(curves);
}

void tnbLib::Marine_WetSection::RetrieveCurvesOnWaterTo
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

std::shared_ptr<tnbLib::Marine_Section> 
tnbLib::Marine_WetSection::Copy() const
{
	auto wire = std::dynamic_pointer_cast<Pln_Wire>(Wire()->Copy());
	Debug_Null_Pointer(wire);

	auto copy = std::make_shared<Marine_WetSection>(Index(), Name(), wire);
	Debug_Null_Pointer(copy);

	copy->SetDeep(DeepCondition());

	return std::move(copy);
}