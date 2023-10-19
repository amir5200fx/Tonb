#include <VoyageFun_CostFunction_Resistane.hxx>

#include <VoyageFun_Resistance.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean
tnbLib::VoyageFun_CostFunction_Resistane::IsValidRange
(
	const Standard_Real theValue,
	const Range& theRange
)
{
	const auto [x0, x1] = theRange;
	return INSIDE(theValue, x0, x1);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::VoyageFun_CostFunction_Resistane::CalcAvgVelocity
(
	const State& theState0, 
	const State& theState1
) const
{
	const auto& p0 = theState0.pos;
	const auto& p1 = theState1.pos;
	auto t0 = theState0.time.value;
	auto t1 = theState1.time.value;
	const auto nbsegments = NbSamples();
	const auto du = 1.0 / static_cast<Standard_Real>(nbsegments);
	const auto dp2 = 0.5 * du * (p1 - p0);
	const auto dt2 = 0.5 * du * (t1 - t0);
	std::vector<Pnt2d> coords;
	std::vector<Standard_Real> times;
	for (Standard_Integer i = 0; i < nbsegments; i++)
	{
		auto p = p0 + i * du - dp2;
		auto t = t0 + i * du - dt2;
		times.emplace_back(t);
		coords.emplace_back(std::move(p));
	}
	Standard_Real sum_u = 0, sum_v = 0;
	for (size_t i = 0; i < coords.size(); i++)
	{
		auto [u, v] = theVelocity_(coords.at(i), times.at(i));
		sum_u += u;
		sum_v += v;
	}
	return { sum_u / NbSamples(), sum_v / NbSamples() };
}

tnbLib::Vec2d
tnbLib::VoyageFun_CostFunction_Resistane::ShipDirect(const Pnt2d& theP0, const Pnt2d& theP1)
{
	auto dp = theP1 - theP0;
	return Vec2d(dp.XY());
}

tnbLib::VoyageFun_CostFunction_Resistane::VoyageFun_CostFunction_Resistane
(
	const VelFun& theVelFun, 
	const std::shared_ptr<VoyageFun_Resistance>& theResistFun,
	const Range& theVelRange,
	const Range& theTimeRange
)
	: theNbSamples_(3)
	, theDist_(0)
	, theTimeRange_(theTimeRange)
	, theVelRange_(theVelRange)
	, theResist_(theResistFun)
	, theVelocity_(theVelFun)
{}

Standard_Real
tnbLib::VoyageFun_CostFunction_Resistane::Value
(const State& theState0, const State& theState1) const
{

	const auto ship_dir = ShipDirect(theState0.pos, theState1.pos).Normalized();
	auto [u, v] = CalcAvgVelocity(theState0, theState1);
	const auto flow_vel = Vec2d(u, v).Dot(ship_dir);
	if (flow_vel < 0)
	{
		return theResist_->Value(std::abs(flow_vel) + ShipVel());
	}
	else
	{
		return theResist_->Value(ShipVel());
	}
}
