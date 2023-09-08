#include <VoyageWP_Connect.hxx>

#include <VoyageWP_Connect.hxx>
#include <VoyageWP_Dist.hxx>
#include <VoyageWP_Net.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::VoyageWP_Connect::Perform()
{
	if (NOT Net())
	{
		FatalErrorIn(FunctionSIG)
			<< "No net has been loaded." << endl
			<< abort(FatalError);
	}
	if (std::abs(Angle()) <= 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid angle has been detected." << endl
			<< " - Angle: " << Angle() << endl
			<< abort(FatalError);
	}
	const auto& net = Net();
	const auto angle = Angle();
	const auto& nodes = net->Nodes();
	for (size_t i = 0; i < nodes.size() - 1; i++)
	{
		auto next_lev = (Standard_Integer)(i + 1);
		const auto& node = nodes.at(i);
		auto wpnts = net->Waypoints(next_lev);
		{//- the dist. algorithm
			auto alg = std::make_shared<VoyageWP_Dist>();
			Debug_Null_Pointer(alg);
			alg->SetMeshInfo(CurveInfo());
			alg->SetMetricInfo(MetricInfo());
			alg->SetEarth(Earth());
			alg->SetMaxSubLev(MaxSubLev());
			alg->SetPoint(node->Coord());
			alg->SetWPs(VoyageWP_Net::RetrieveCoords(wpnts));

			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed.");
			auto iMin = alg->MinDistance();
			auto iMax_star = alg->MaxStarAngle(angle);
			auto iMax_port = alg->MaxPortAngle(angle);

			if (INSIDE(iMin, iMax_star, iMax_port))
			{
				auto next_nodes = net->RetrieveWaypoints(next_lev, iMax_star, iMax_port);
				for (const auto& n : next_nodes)
				{
					Debug_Null_Pointer(n);
					node->InsertNode(n->Index(), n);
				}
			}
			else
			{
				auto next = wpnts.at(iMin);
				node->InsertNode(next->Index(), node);
			}
		}
	}
	Change_IsDone() = Standard_True;
}