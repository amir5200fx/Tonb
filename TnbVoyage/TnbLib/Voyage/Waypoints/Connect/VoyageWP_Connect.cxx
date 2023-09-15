#include <VoyageWP_Connect.hxx>

#include <VoyageWP_Dist.hxx>
#include <VoyageWP_Net.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer tnbLib::VoyageWP_Connect::DEFAULT_SUB_LEV(5);

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
	const auto& nodes = net->Nodes();
	{// connect the ref. nodes
		
		for (size_t i = 0; i < nodes.size() - 1; i++)
		{
			const auto& n0 = nodes.at(i);
			const auto& n1 = nodes.at(i + 1);
			n0->InsertNode(n1->Index(), n1);
		}
	}
	//const auto angle = std::cos(Angle());
	const auto angle = Angle();
	std::cout << "ANGLE = " << angle << std::endl;
	for (size_t i = 0; i < nodes.size() - 1; i++)
	{
		std::cout << "id = " << i << std::endl;
		
		const auto next_lev = (Standard_Integer)(i + 1);
		const auto& node = nodes.at(i);
		// get the sorted nodes from the starboard to the port (including the ref. node).
		auto wpnts = net->SortedWaypoints(next_lev);
		{//- the dist. algorithm
			auto alg = std::make_shared<VoyageWP_Dist>();
			Debug_Null_Pointer(alg);
			alg->SetMeshInfo(CurveInfo());
			alg->SetMetricInfo(MetricInfo());
			alg->SetEarth(Earth());
			alg->SetMaxSubLev(MaxSubLev());
			alg->SetPoint(node->Coord());
			alg->SetWPs(VoyageWP_Net::RetrieveCoords(wpnts));
			/*
			 * calc. the distance bertween two consecutive nodes of the wps and
			 * the distance between the current node and the waypoints ahead.
			 */
			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed.");
			/*
			 * Loccate the node from the wps with the minimum distance between it and the current
			 * node.
			 */
			const auto iMin = alg->MinDistanceId();
			/*
			 * Locate the starboard side node from the wps that make the maximum angle
			 * with the current node.
			 */
			const auto iMax_star = alg->MaxStarAngle(angle);
			//PAUSE;
			/*
			 * Locate the port side node from the wps that make the maximum angle
			 * with the current node.
			 */
			const auto iMax_port = alg->MaxPortAngle(angle);
			std::cout << "imin: " << iMin << ", i star: " << iMax_star << ", i port: " << iMax_port << std::endl;
			//std::exit(1);
			PAUSE;
			if (INSIDE(iMin, iMax_star, iMax_port))
			{
				auto next_nodes = 
					net->RetrieveWaypoints(next_lev, iMax_star, iMax_port);
				for (const auto& n : next_nodes)
				{
					Debug_Null_Pointer(n);
					if (NOT n->IsReference())
					{
						node->InsertNode(n->Index(), n);
					}
				}
			}
			else
			{
				const auto next = wpnts.at(iMin);
				node->InsertNode(next->Index(), node);
			}
		}
	}
	Change_IsDone() = Standard_True;
}