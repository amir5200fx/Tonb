#include <HydStatic_TankCapacityCurveQ.hxx>

void tnbLib::HydStatic_TankCapacityCurveQ::Check()
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

tnbLib::HydStatic_TankCapacityCurveQ::HydStatic_TankCapacityCurveQ
(
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
)
	: HydStatic_HydOffsetCurve(theQs)
{
	Check();
}

tnbLib::HydStatic_TankCapacityCurveQ::HydStatic_TankCapacityCurveQ
(
	std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
)
	: HydStatic_HydOffsetCurve(std::move(theQs))
{
	Check();
}

tnbLib::HydStatic_TankCapacityCurveQ::HydStatic_TankCapacityCurveQ
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
)
	: HydStatic_HydOffsetCurve(theIndex, theName, theQs)
{
	Check();
}

tnbLib::HydStatic_TankCapacityCurveQ::HydStatic_TankCapacityCurveQ
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
tnbLib::HydStatic_TankCapacityCurveQ::FirstVolume() const
{
	return FirstValue();
}

Standard_Real 
tnbLib::HydStatic_TankCapacityCurveQ::LastVolume() const
{
	return LastValue();
}

Standard_Real 
tnbLib::HydStatic_TankCapacityCurveQ::MaxVolume() const
{
	return LastValue();
}

Standard_Real 
tnbLib::HydStatic_TankCapacityCurveQ::LowerZ() const
{
	return Lower();
}

Standard_Real 
tnbLib::HydStatic_TankCapacityCurveQ::UpperZ() const
{
	return Upper();
}

Standard_Real 
tnbLib::HydStatic_TankCapacityCurveQ::Volume(const Standard_Real theZ) const
{
	return Value(theZ);
}

void tnbLib::HydStatic_TankCapacityCurveQ::SetQs
(
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
)
{
	HydStatic_HydOffsetCurve::SetQs(theQs);
	Check();
}

void tnbLib::HydStatic_TankCapacityCurveQ::SetQs
(
	std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
)
{
	HydStatic_HydOffsetCurve::SetQs(std::move(theQs));
	Check();
}