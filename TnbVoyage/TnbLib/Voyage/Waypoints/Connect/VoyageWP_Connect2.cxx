#include <VoyageWP_Connect2.hxx>

#include <VoyageWP_Net.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::VoyageWP_Connect2::Perform()
{
	if (NOT Net())
	{
		FatalErrorIn(FunctionSIG)
			<< "No net has been loaded." << endl
			<< abort(FatalError);
	}
	const auto& net = Net();
	const auto& nodes = net->Nodes();
	//std::cout << "nb nodes = " << nodes.size() << std::endl;
	for (size_t i = 0; i < nodes.size() - 1; i++)
	{
		//std::cout << "i = " << i << std::endl;
		//if (i > 10) break;
		const auto& ref = nodes.at(i);
		ref->SetSense(Standard_True);
		//const auto& next = nodes.at(i + 1);
		const auto max_starboard = net->NbStarboards(i + 1);
		const auto max_port = net->NbPorts(i + 1);
		Debug_Null_Pointer(ref);
		if (ref->IsInterior())
		{
			const auto interior =
				std::dynamic_pointer_cast<VoyageWP_Net::InterNode>(ref);
			Debug_Null_Pointer(interior);
			{// the starboard side
				const auto& sides = interior->Starboards();
				Standard_Integer lev = 0;
				for (const auto& wp:sides)
				{
					Debug_Null_Pointer(wp.second);
					const auto& current = wp.second;
					if (NOT current->Sense()) continue;
					--lev;
					auto i_min = lev - Size();
					auto i_max = lev + Size();
					//std::cout << " i min = " << i_min << ", i_max = " << i_max << std::endl;
					i_min = std::max(i_min, -max_starboard);
					i_max = std::min(i_max, max_port);
					//std::cout << " i min1 = " << i_min << ", i_max1 = " << i_max << std::endl;
					i_min += max_starboard;
					i_max += max_starboard;
					//std::cout << " i min2 = " << i_min << ", i_max2 = " << i_max << std::endl;
					//std::cout << std::endl;
					if (i_max < i_min)
					{
						continue;
					}
					auto next_nodes = 
						net->RetrieveWaypoints(i + 1, i_min, i_max);
					//std::cout << "injaaaaa" << std::endl;
					for (const auto& next:next_nodes)
					{
						Debug_Null_Pointer(next);
						if (theStateFun_(current->Coord(), next->Coord()))
						{
							current->InsertNode(next->Index(), next);
							next->SetSense(Standard_True);
						}
					}
					
				}
			}
			//PAUSE;
			{ // the ref node
				const Standard_Integer lev = 0;
				auto i_min = lev - Size();
				auto i_max = lev + Size();
				i_min = std::max(i_min, -max_starboard);
				i_max = std::min(i_max, max_port);
				i_min += max_starboard;
				i_max += max_starboard;
				auto next_nodes =
					net->RetrieveWaypoints(i + 1, i_min, i_max);
				if (i_max < i_min)
				{
					continue;
				}
				for (const auto& next : next_nodes)
				{
					Debug_Null_Pointer(next);
					if (next->IsReference())
					{
						if (theStateFun_(ref->Coord(), next->Coord()))
						{
							ref->InsertNode(next->Index(), next);
							next->SetSense(Standard_True);
						}
					}
					else if (theStateFun_(ref->Coord(), next->Coord()))
					{
						ref->InsertNode(next->Index(), next);
						next->SetSense(Standard_True);
					}
				}
			}
			{// the port side
				const auto& sides = interior->Ports();
				Standard_Integer lev = 0;
				for (const auto& wp:sides)
				{
					Debug_Null_Pointer(wp.second);
					const auto& current = wp.second;
					if (NOT current->Sense()) continue;
					++lev;
					auto i_min = lev - Size();
					auto i_max = lev + Size();
					i_min = std::max(i_min, -max_starboard);
					i_max = std::min(i_max, max_port);
					i_min += max_starboard;
					i_max += max_starboard;
					if (i_max < i_min)
					{
						continue;
					}
					auto next_nodes =
						net->RetrieveWaypoints(i + 1, i_min, i_max);
					for (const auto& next : next_nodes)
					{
						Debug_Null_Pointer(next);
						if (theStateFun_(current->Coord(), next->Coord()))
						{
							current->InsertNode(next->Index(), next);
							next->SetSense(Standard_True);
						}
					}
				}
			}
		}
		else
		{
			if (ref->IsDeparture())
			{
				//const auto& next = nodes.at(i + 1);
				//Debug_Null_Pointer(next);
				//ref->InsertNode(next->Index(), next);
				const Standard_Integer lev = 0;
				auto i_min = lev - Size();
				auto i_max = lev + Size();
				i_min = std::max(i_min, -max_starboard);
				i_max = std::min(i_max, max_port);
				i_min += max_starboard;
				i_max += max_starboard;
				if (i_max < i_min)
				{
					continue;
				}
				auto next_nodes =
					net->RetrieveWaypoints(i + 1, i_min, i_max);
				for (const auto& next : next_nodes)
				{
					Debug_Null_Pointer(next);
					if (next->IsReference())
					{
						if (theStateFun_(ref->Coord(), next->Coord()))
						{
							ref->InsertNode(next->Index(), next);
							next->SetSense(Standard_True);
						}
					}
					else if (theStateFun_(ref->Coord(), next->Coord()))
					{
						ref->InsertNode(next->Index(), next);
						next->SetSense(Standard_True);
					}
				}
			}
		}
	}
	Change_IsDone() = Standard_True;
}
