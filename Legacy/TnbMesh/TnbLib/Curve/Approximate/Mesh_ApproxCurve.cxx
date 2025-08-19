#include <Mesh_ApproxCurve.hxx>

std::vector<Standard_Real> tnbLib::Mesh_ApproxCurveBase::Tessellate(const std::vector<Standard_Real>& us,
	Standard_Integer theMinSamples)
{
	std::vector<Standard_Real> ts;
	for (size_t i = 0; i < us.size() - 1; i++)
	{
		ts.emplace_back(us.at(i));
		ts.emplace_back(MEAN(us.at(i), us.at(i + 1)));
	}
	ts.emplace_back(us.at(us.size() - 1));
	if (ts.size() < theMinSamples)
	{
		return Tessellate(ts, theMinSamples);
	}
	return std::move(ts);
}
