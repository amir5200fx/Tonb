#include <HydStatic_FillCurveQ.hxx>

void tnbLib::HydStatic_FillCurveQ::Check()
{
	auto iter = Qs().begin();
	auto z0 = iter->second;
	
	iter++;
	while (iter NOT_EQUAL Qs().end())
	{
		if (iter->second <= z0)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid data for a filling curve" << endl
				<< abort(FatalError);
		}
		iter++;
	}
}

tnbLib::HydStatic_FillCurveQ::HydStatic_FillCurveQ
(
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
)
	: HydStatic_HydOffsetCurve(theQs)
{
	Check();
}

tnbLib::HydStatic_FillCurveQ::HydStatic_FillCurveQ
(
	std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
)
	: HydStatic_HydOffsetCurve(std::move(theQs))
{
	Check();
}

tnbLib::HydStatic_FillCurveQ::HydStatic_FillCurveQ
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
)
	: HydStatic_HydOffsetCurve(theIndex, theName, theQs)
{
	Check();
}

tnbLib::HydStatic_FillCurveQ::HydStatic_FillCurveQ
(
	const Standard_Integer theIndex,
	const word & theName, 
	std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
)
	: HydStatic_HydOffsetCurve(theIndex, theName, std::move(theQs))
{
	Check();
}

Standard_Real 
tnbLib::HydStatic_FillCurveQ::FirstVolume() const
{
	return FirstValue();
}

Standard_Real 
tnbLib::HydStatic_FillCurveQ::LastVolume() const
{
	return LastValue();
}

Standard_Real 
tnbLib::HydStatic_FillCurveQ::MaxVolume() const
{
	return LastValue();
}

Standard_Real 
tnbLib::HydStatic_FillCurveQ::LowerZ() const
{
	return Lower();
}

Standard_Real 
tnbLib::HydStatic_FillCurveQ::UpperZ() const
{
	return Upper();
}

Standard_Real 
tnbLib::HydStatic_FillCurveQ::Volume(const Standard_Real theZ) const
{
	return Value(theZ);
}

void tnbLib::HydStatic_FillCurveQ::SetQs
(
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
)
{
	HydStatic_HydOffsetCurve::SetQs(theQs);
	Check();
}

void tnbLib::HydStatic_FillCurveQ::SetQs
(
	std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
)
{
	HydStatic_HydOffsetCurve::SetQs(std::move(theQs));
	Check();
}