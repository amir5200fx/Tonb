#include <Marine_Section_Wetted.hxx>

#include <Pln_Wire.hxx>
#include <Marine_PlnCurves.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Marine_SectTools.hxx>
#include <Pln_Wire.hxx>

void tnbLib::marineLib::Section_Wetted::CheckCurves() const
{
	Debug_Null_Pointer(Wire());
	const auto& curves = Wire()->RetrieveCurves();
	for (const auto& x : curves)
	{
		if (NOT(Marine_SectTools::IsWetted(x) OR Marine_SectTools::IsWater(x)))
		{
			FatalErrorIn(FunctionSIG)
				<< " the curve is supposed to be wetted!" << endl
				<< abort(FatalError);
		}
	}
}

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

template<>
std::shared_ptr<tnbLib::Marine_Section> 
tnbLib::marineLib::InnerSection<tnbLib::marineLib::Section_Wetted>::Copy() const
{
	auto wire = std::dynamic_pointer_cast<Pln_Wire>(this->Wire()->Copy());
	Debug_Null_Pointer(wire);

	auto copy = std::make_shared<InnerSection<Section_Wetted>>(this->Index(), this->Name(), wire);
	Debug_Null_Pointer(copy);

	copy->SetDeep(DeepCondition());

	return std::move(copy);
}

template<>
std::shared_ptr<tnbLib::Marine_Section>
tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Wetted>::Copy() const
{
	auto wire = std::dynamic_pointer_cast<Pln_Wire>(this->Wire()->Copy());
	Debug_Null_Pointer(wire);

	auto copy = std::make_shared<OuterSection<Section_Wetted>>(this->Index(), this->Name(), wire);
	Debug_Null_Pointer(copy);
	for (const auto& x : Inners())
	{
		Debug_Null_Pointer(x.second);
		auto c = std::dynamic_pointer_cast<InnerSection<Section_Wetted>>(x.second->Copy());
		copy->ImportToInners(x.first, c);

		c->SetOuter(copy);
	}
	copy->SetDeep(DeepCondition());
	return std::move(copy);
}