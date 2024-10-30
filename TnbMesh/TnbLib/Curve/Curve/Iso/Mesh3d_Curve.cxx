#include <Mesh3d_Curve.hxx>

namespace tnbLib
{

	template<>
	void Mesh_Curve<Geom_Curve, Geo3d_MetricPrcsr, true>::MakeChain
	(
		const std::vector<Standard_Real>& theParameters
	)
	{
		theChain_ = std::make_shared<Entity_Polygon<std::pair<Pnt3d, Standard_Real>>>();

		auto& Points = theChain_->Points();
		Points.reserve(theParameters.size());

		const auto& curve = *theCurve_;
		for (const auto x : theParameters)
		{
			auto pt = curve.Value(x);
			auto paired = std::make_pair(std::move(pt), x);
			Points.push_back(std::move(paired));
		}
	}
}