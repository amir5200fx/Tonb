#include <VoyageSim_GetTimeline.hxx>

#include <VoyageSim_MinFuel.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageSim_GetTimeline::Find(const Pnt2d& theCoord, const Standard_Real theRadius) const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the application is not performed." << endl
			<< abort(FatalError);
	}
	std::vector<std::shared_ptr<VoyageWP_Net::Node>> items;
	theEngine_->GeometrySearch(theRadius, theCoord, items);
	return std::move(items);
}

std::vector<Standard_Real>
tnbLib::VoyageSim_GetTimeline::Timeline(const Standard_Integer theIndex) const
{
	if (NOT Simulation())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No simulation has been found." << endl
			<< abort(FatalError);
	}
	const auto& sim = Simulation();
	const auto iter = sim->Timelines().find(theIndex);
	if (iter IS_EQUAL sim->Timelines().end())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the item is not in the tree!" << endl
			<< " - id: " << theIndex << endl
			<< abort(FatalError);
	}
	return iter->second;
}

void tnbLib::VoyageSim_GetTimeline::Perform()
{
	if (NOT Simulation())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No simulation has been found." << endl
			<< abort(FatalError);
	}
	const auto& sim = Simulation();
	const auto& net = sim->Net();
	if (NOT net)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Couldn't find the net of the simulation." << endl
			<< abort(FatalError);
	}
	const auto bound_box = Geo_BoxTools::GetBox(net->RetrieveCoords(), 1.0E-4);
	theEngine_ = std::make_shared<Geo_AdTree<std::shared_ptr<Node>>>();
	theEngine_->SetGeometryRegion(bound_box);
	theEngine_->SetGeometryCoordFunc([](const std::shared_ptr<Node>& n) {return n->node->Coord(); });
	for (const auto& x: net->RetrieveNodes())
	{
		Debug_Null_Pointer(x);
		Node node{ x };
		theEngine_->InsertToGeometry(std::make_shared<Node>(node));
	}
	Change_IsDone() = Standard_True;
}
