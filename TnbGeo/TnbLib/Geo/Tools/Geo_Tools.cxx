#include <Geo_Tools.hxx>

#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_Triangulation.hxx>

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Geo_Tools::RetrieveChain
(
	const Entity2d_Polygon & thePoly
)
{
	auto chain = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(chain);

	chain->Points() = thePoly.Points();
	chain->Connectivity() = dualConnectivityList_Chain(thePoly.NbPoints() - 1);
	
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Geo_Tools::RetrieveChain
(
	const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePoly
)
{
	auto chain = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	auto& indices = chain->Connectivity();

	Standard_Integer nbPts = 0;
	for (const auto& poly : thePoly)
	{
		Debug_Null_Pointer(poly);

		for (const auto& pt : poly->Points())
		{
			pts.push_back(pt);
		}

		auto l = 
			dualConnectivityList_Chain(poly->NbPoints() - 1);
		for (const auto& x : l)
		{
			auto i0 = x.Value(0) + nbPts;
			auto i1 = x.Value(1) + nbPts;

			connectivity::dual edge;

			edge.Value(0) = i0;
			edge.Value(1) = i1;

			indices.push_back(std::move(edge));
		}

		nbPts += poly->NbPoints();
	}
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Chain>
tnbLib::Geo_Tools::RetrieveChain
(
	const std::vector<std::shared_ptr<Entity3d_Polygon>>& thePoly
)
{
	auto chain = std::make_shared<Entity3d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	auto& indices = chain->Connectivity();

	Standard_Integer nbPts = 0;
	for (const auto& poly : thePoly)
	{
		Debug_Null_Pointer(poly);

		for (const auto& pt : poly->Points())
		{
			pts.push_back(pt);
		}

		auto l =
			dualConnectivityList_Chain(poly->NbPoints() - 1);
		for (const auto& x : l)
		{
			auto i0 = x.Value(0) + nbPts;
			auto i1 = x.Value(1) + nbPts;

			connectivity::dual edge;

			edge.Value(0) = i0;
			edge.Value(1) = i1;

			indices.push_back(std::move(edge));
		}

		nbPts += poly->NbPoints();
	}
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Chain>
tnbLib::Geo_Tools::RetrieveChain
(
	const std::vector<std::shared_ptr<Entity3d_Chain>>& theChains
)
{
	auto chain = std::make_shared<Entity3d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	auto& indices = chain->Connectivity();

	Standard_Integer nbPts = 0;
	for (const auto& ch : theChains)
	{
		Debug_Null_Pointer(ch);

		for (const auto& pt : ch->Points())
		{
			pts.push_back(pt);
		}

		for (const auto& x : ch->Connectivity())
		{
			auto i0 = x.Value(0) + nbPts;
			auto i1 = x.Value(1) + nbPts;

			connectivity::dual edge;

			edge.Value(0) = i0;
			edge.Value(1) = i1;

			indices.push_back(std::move(edge));
		}

		nbPts += ch->NbPoints();
	}
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Triangulation> 
tnbLib::Geo_Tools::Triangulation
(
	const Entity3d_Chain & theChain
)
{
	auto tr = std::make_shared<Entity3d_Triangulation>();
	Debug_Null_Pointer(tr);

	auto& pts = tr->Points();
	auto& indices = tr->Connectivity();

	pts = theChain.Points();
	for (const auto& x : theChain.Connectivity())
	{
		auto i0 = x.Value(0);
		auto i1 = x.Value(1);

		connectivity::triple t;
		t.Value(0) = i0;
		t.Value(1) = i1;
		t.Value(2) = i0;

		indices.push_back(std::move(t));
	}
	return std::move(tr);
}