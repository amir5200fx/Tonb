#include "VoyageWP_PointDistb.hxx"

#include <VoyageWP_PointDistb.hxx>

#include <VoyageWP_Net.hxx>
#include <Voyage_OffsetProfile.hxx>
#include <VoyageWP_Offset.hxx>
#include <VoyageGeo_Earth.hxx>
#include <Mesh2d_CurveAnIso.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Polygon.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	auto RetrieveOffsets(const Entity2d_Polygon& thePoly)
	{
		std::vector<Pnt2d> coords;
		coords.reserve(thePoly.NbPoints() - 1);
		const auto& points = thePoly.Points();
		for (size_t i = 1; i < points.size(); i++)
		{
			coords.push_back(points.at(i));
		}
		auto poly = 
			std::make_shared<Entity2d_Polygon>
		(std::move(coords), 0);
		return std::move(poly);
	}

}

void tnbLib::VoyageWP_PointDistb::Perform()
{
	if (NOT Size())
	{
		FatalErrorIn(FunctionSIG)
			<< "No size has been set." << endl
			<< abort(FatalError);
	}
	const auto size = Size();
	if (NOT Offsets())
	{
		FatalErrorIn(FunctionSIG)
			<< "No offsets has been set." << endl
			<< abort(FatalError);
	}
	const auto& offsets = Offsets();
	if (NOT Profile())
	{
		FatalErrorIn(FunctionSIG)
			<< "No profile has been set." << endl
			<< abort(FatalError);
	}
	const auto& profile = Profile();
	if (NOT Earth())
	{
		FatalErrorIn(FunctionSIG)
			<< "the earth has been set." << endl
			<< abort(FatalError);
	}
	const auto& earth = Earth();
	if (NOT CurveInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "No curve info. has been set." << endl
			<< abort(FatalError);
	}
	const auto& curve_info = CurveInfo();
	if (NOT IntegInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "No integ. info. has been set." << endl
			<< abort(FatalError);
	}
	auto metricInfo = std::make_shared<Geo_MetricPrcsrAnIso_Info>();
	metricInfo->OverrideIntegInfo(IntegInfo());
	auto metrics = earth->GetMetrics();

	auto sizeFun =
		std::make_shared<GeoSizeFun2d_Uniform>
		(size, metrics->BoundingBox());

	auto metricPrcsr =
		std::make_shared<Geo2d_MetricPrcsrAnIso>(sizeFun, metrics, metricInfo);
	const auto nodes = offsets->RetrieveInteriors();
	Standard_Integer nb_nodes = 0;
	std::vector<std::shared_ptr<RefNode>> ref_nodes;
	{//- the departure node
		const auto node = offsets->Departure();
		Debug_Null_Pointer(node);
		auto ref_node = std::make_shared<DepNode>(++nb_nodes, node->Coord());
		ref_nodes.push_back(std::move(ref_node));
	}
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x);
		std::shared_ptr<Entity2d_Polygon> star_poly;
		{//- the starboard profile
			const auto node = 
				std::dynamic_pointer_cast<VoyageWP_Offset::InterNode>(x);
			Debug_Null_Pointer(node);
			auto [p0, p1] = node->StarboardProfile();
			const auto curve = profile->Geometry(p0, p1);
			const auto& geom = curve->Geometry();
			const auto alg =
				std::make_shared<Mesh2d_CurveAnIso>
				(
					geom,
					geom->FirstParameter(), geom->LastParameter(),
					metricPrcsr, curve_info
				);
			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed.");
			star_poly = RetrieveOffsets(*alg->Mesh());
		}
		std::shared_ptr<Entity2d_Polygon> port_poly;
		{//- the port profile
			const auto node = 
				std::dynamic_pointer_cast<VoyageWP_Offset::InterNode>(x);
			Debug_Null_Pointer(node);
			auto [p0, p1] = node->PortProfile();
			const auto curve = profile->Geometry(p0, p1);
			const auto& geom = curve->Geometry();
			const auto alg =
				std::make_shared<Mesh2d_CurveAnIso>
				(
					geom,
					geom->FirstParameter(), geom->LastParameter(),
					metricPrcsr, curve_info
				);
			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed.");
			port_poly = RetrieveOffsets(*alg->Mesh());
		}
		auto star_side = std::make_shared<StarSide>();
		star_side->SetOffsets(star_poly);
		auto port_side = std::make_shared<PortSide>();
		port_side->SetOffsets(port_poly);

		auto ref_node = std::make_shared<InterNode>(++nb_nodes, x->Coord());
		ref_node->SetStarboard(star_side);
		ref_node->SetPort(port_side);

		ref_nodes.push_back(std::move(ref_node));
	}
	{//- the arrival node
		const auto node = offsets->Arrival();
		Debug_Null_Pointer(node);
		auto ref_node = std::make_shared<ArvNode>(++nb_nodes, node->Coord());
		ref_nodes.push_back(std::move(ref_node));
	}
	theNodes_ = std::move(ref_nodes);
	Change_IsDone() = Standard_True;
}

std::shared_ptr<tnbLib::VoyageWP_Net> 
tnbLib::VoyageWP_PointDistb::RetrieveNet() const
{
	const auto net = std::make_shared<VoyageWP_Net>();
	Debug_Null_Pointer(net);
	// getting the nodes
	auto& nodes = net->NodesRef();
	Standard_Integer nb_nodes = 0;
	for (const auto& x:theNodes_)
	{
		Debug_Null_Pointer(x);
		if(x->IsDeparture())
		{
			auto node = std::make_shared<VoyageWP_Net::DepNode>(++nb_nodes, x->Coord());
			nodes.emplace_back(std::move(node));
			continue;
		}
		if(x->IsArrival())
		{
			auto node = std::make_shared<VoyageWP_Net::ArvNode>(++nb_nodes, x->Coord());
			nodes.emplace_back(std::move(node));
			continue;
		}
		// the node is interior
		auto node = std::make_shared<VoyageWP_Net::InterNode>(++nb_nodes, x->Coord());
		Debug_Null_Pointer(node);
		nodes.emplace_back(node);
		// the starboard side nodes
		const auto interior = std::dynamic_pointer_cast<InterNode>(x);
		Debug_Null_Pointer(interior);
		Debug_Null_Pointer(interior->Starboard());
		const auto& star_side = interior->Starboard();
		if (star_side->Offsets())
		{
			for (const auto& p : star_side->Offsets()->Points())
			{
				auto wp = std::make_shared<VoyageWP_Net::WPNode>(++nb_nodes, p);
				node->InsertToStarboard(wp->Index(), wp);
			}
		}
		Debug_Null_Pointer(interior->Port());
		// the port side nodes
		const auto& port_side = interior->Port();
		if (port_side->Offsets())
		{
			for (const auto& p:port_side->Offsets()->Points())
			{
				auto wp = std::make_shared<VoyageWP_Net::WPNode>(++nb_nodes, p);
				node->InsertToPort(wp->Index(), wp);
			}
		}
	}
	return std::move(net);
}