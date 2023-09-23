#include <VoyageSim_MinFuel.hxx>

#include <VoyageWP_Net.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::VoyageSim_MinFuel::Perform()
{
	std::vector<Standard_Real> velocities; // taking care of it later
	auto net = std::make_shared<VoyageWP_Net>();
	for (const auto& x: Net()->Nodes())
	{
		auto current_time = x->Time();
		const auto& nexts = x->Nexts();
		for (const auto& [id, next]: nexts)
		{
			Debug_Null_Pointer(next);
			const auto dist = theDist_(x->Coord(), next->Coord());
			std::vector<Standard_Real> times;
			times.reserve(velocities.size());
			for (const auto current_vel : velocities)
			{
				const auto next_time = dist / current_vel;
				times.emplace_back(next_time);
			}
			std::vector<Standard_Real> resists;
			resists.reserve(velocities.size());
			for (const auto ti: times)
			{
				auto resist = theResistFun_({ x->Coord(),current_time }, { next->Coord(),ti }, dist, NbSamples());
				resists.emplace_back(resist);
			}
		}
	}
}
