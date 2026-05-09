#include <PtdShapeFit_ProjMeshToFace.hxx>

#include <Cad_GeomSurface.hxx>
#include <Entity3d_TriangulationPatch.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom_BoundedSurface.hxx>

std::shared_ptr<tnbLib::Entity3d_Polygon> 
tnbLib::PtdShapeFit_ProjMeshToFace::GetPolygon
(
	const std::vector<Pnt3d>& thePnts,
	const std::vector<connectivity::dual>& theIds
)
{
	std::vector<Pnt3d> pnts;
	auto iter = theIds.begin();
	auto v0 = iter->Value(0);
	auto v1 = iter->Value(1);

	pnts.push_back(thePnts.at(Index_Of(v0)));
	iter++;
	while (iter NOT_EQUAL theIds.end())
	{
		v0 = iter->Value(0);
		v1 = iter->Value(1);
		pnts.push_back(thePnts.at(Index_Of(v0)));
		iter++;
	}
	pnts.push_back(thePnts.at(Index_Of(v1)));

	auto poly = std::make_shared<Entity3d_Polygon>(std::move(pnts), 0);
	return std::move(poly);
}

std::vector<std::shared_ptr<tnbLib::PtdShapeFit_ProjMeshToFace::Node3d>>
tnbLib::PtdShapeFit_ProjMeshToFace::GetNodes(const Entity3d_Polygon& thePoly)
{
	const auto& pnts = thePoly.Points();
	std::vector<std::shared_ptr<Node3d>> nodes;
	nodes.reserve(pnts.size());
	for (const auto& x : pnts)
	{
		Node3d nodeRef = { x,nullptr };
		auto node = std::make_shared<Node3d>(std::move(nodeRef));
		nodes.push_back(std::move(node));
	}
	return std::move(nodes);
}

void tnbLib::PtdShapeFit_ProjMeshToFace::Perform()
{
	if (NOT Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Face())
	{
		FatalErrorIn(FunctionSIG)
			<< "no face has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Boundary())
	{
		FatalErrorIn(FunctionSIG)
			<< "no boundary has been loaded." << endl
			<< abort(FatalError);
	}
	const auto& outer = Boundary();

	auto gPoly = GetPolygon(Mesh()->Points(), *outer);
	auto nodes = GetNodes(*gPoly);

	const auto& g = Face()->Geometry();
	if (NOT Handle(Geom_BoundedSurface)::DownCast(g))
	{
		FatalErrorIn(FunctionSIG)
			<< "the surface is not bounded." << endl
			<< abort(FatalError);
	}

	const auto umin = Face()->FirstParameterU();
	const auto umax = Face()->LastParameterU();
	const auto vmin = Face()->FirstParameterV();
	const auto vmax = Face()->LastParameterV();

	try
	{
		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			const auto& coord3d = x->coord;
			GeomAPI_ProjectPointOnSurf projObj;
			projObj.Init(coord3d, g, umin, umax, vmin, vmax);
			projObj.Perform(coord3d);

			Standard_Real u, v;
			projObj.LowerDistanceParameters(u, v);

			Pnt2d p2(u, v);
			Node2d nodeRef = { std::move(p2),x };
			auto node = std::make_shared<Node2d>(std::move(nodeRef));
			node->parent = x;
			x->parNode = std::move(node);
		}
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< " couldn't project the point: " << endl
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}
	theNodes_ = std::move(nodes);
	Change_IsDone() = Standard_True;
}