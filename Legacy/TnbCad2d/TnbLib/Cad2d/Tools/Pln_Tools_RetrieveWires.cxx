#include <Pln_Tools.hxx>

#include <Geo_Tools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Wire.hxx>
#include <Pln_CmpEdge.hxx>
#include <Cad2d_RemoveNonManifold.hxx>
#include <Adt_AvlTree.hxx>

#include <OFstream.hxx>
#include <TecPlot.hxx>

tnbLib::Pln_Orientation 
tnbLib::Pln_Tools::RetrieveOrientation
(
	const Pln_Wire & theWire
)
{
	std::vector<Pnt2d> Pts;

	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		if (!x->Mesh())
		{
			FatalErrorIn("Plane_Orientation RetrieveOrientation(const Plane_Wire& theWire)")
				<< " the edge has not an approximation curve!" << endl
				<< abort(FatalError);
		}

		const auto& chain = x->Mesh();
		const auto& appx_pts = chain->Points();

		if (NOT x->Sense())
		{
			const auto c = appx_pts.size() - 1;

			forThose(Index, 0, appx_pts.size() - 2)
			{
				Pts.push_back(appx_pts[c - Index]);
			}
		}
		else
		{
			forThose(Index, 0, appx_pts.size() - 2)
			{
				Pts.push_back(appx_pts[Index]);
			}
		}

		/*for (const auto& x : Pts)
		{
			std::cout << x << std::endl;
		}*/
		/*for (const auto& pt : appx_pts)
		{
			Pts.push_back(pt);
		}*/
	}

#ifdef _DEBUG
	if (NOT Geo_Tools::IsSimple_cgal(Pts))
	{
		Warning << " the polygon is not simple!" << endl
			<< " - Please check the data." << endl;
	}
	else
	{
		if (Geo_Tools::IsCcwOrder_cgal(Pts) NOT_EQUAL Geo_Tools::IsCcwOrder(Pts))
		{
			/*std::cout << (Geo_Tools::IsCcwOrder_cgal(Pts) ? "yes" : "no") << std::endl;
			std::cout << (Geo_Tools::IsCcwOrder(Pts) ? "yes" : "no") << std::endl;

			OFstream myFile(fileName("polygon.plt"));
			Io::ExportCurve(Pts, myFile);*/

			FatalErrorIn(FunctionSIG)
				<< "contradictory results are detected!" << endl
				<< abort(FatalError);
		}
	}
#endif // _DEBUG


	/*if (Geo_Tools::IsCcwOrder_cgal(Pts)) return Pln_Orientation::Pln_Orientation_CCW;
	else return Pln_Orientation::Pln_Orientation_CW;*/
	if (Geo_Tools::IsCcwOrder(Pts)) return Pln_Orientation::Pln_Orientation_CCW;
	else return Pln_Orientation::Pln_Orientation_CW;
}

namespace tnbLib
{
	namespace retrieveWires
	{
		std::shared_ptr<Pln_Edge>
			NextEdge
			(
				const std::shared_ptr<Pln_Edge>& theEdge,
				const std::shared_ptr<Pln_Vertex>& vtx
			)
		{
			if (theEdge->IsRing())
			{
				FatalErrorIn("std::shared_ptr<Pln_Edge> Next(const std::shared_ptr<Pln_Edge>& theEdge)")
					<< "Invalid wire: contains at least one ring!" << endl
					<< abort(FatalError);
			}

			if (NOT vtx)
			{
				FatalErrorIn("std::shared_ptr<Plane_Edge> Next(const std::shared_ptr<Plane_Edge>& theEdge)")
					<< "Null vertex" << endl
					<< abort(FatalError);
			}

			if (NOT vtx->IsManifold())
			{
				FatalErrorIn("std::shared_ptr<Plane_Edge> Next(const std::shared_ptr<Plane_Edge>& theEdge)")
					<< "The vertex is non-manifold" << endl
					<< abort(FatalError);
			}

			const auto& edges = vtx->RetrieveEdges();

			Debug_If_Condition(edges.size() NOT_EQUAL 2);

			Debug_Null_Pointer(edges[0].lock());
			Debug_Null_Pointer(edges[1].lock());

			if (edges[0].lock() IS_EQUAL theEdge)
			{
				return edges[1].lock();
			}
			if (edges[1].lock() IS_EQUAL theEdge)
			{
				return edges[0].lock();
			}
			FatalErrorIn(FunctionSIG)
				<< "Unable to find the next edge" << endl
				<< abort(FatalError);
			return nullptr;
		}

		std::shared_ptr<Pln_Vertex>
			NextNode
			(
				const std::shared_ptr<Pln_Vertex>& theNode,
				const std::shared_ptr<Pln_Edge>& theEdge
			)
		{
			Debug_Null_Pointer(theNode);
			Debug_Null_Pointer(theEdge);

			const auto v0 = theEdge->FirstVtx();
			const auto v1 = theEdge->LastVtx();

			if (v0 IS_EQUAL theNode)
			{
				return v1;
			}
			if (v1 IS_EQUAL theNode)
			{
				return v0;
			}
			return nullptr;
		}
	}

	//.
	// This piece of code should be deleted in the future.
	//.
	//
	//std::shared_ptr<Pln_Wire>
	//	TrackWire
	//	(
	//		Adt_AvlTree<std::shared_ptr<Pln_Edge>>& theRegister
	//	)
	//{
	//	if (theRegister.IsEmpty())
	//	{
	//		FatalErrorIn("wire_ptr TrackWire(Adt_AvlTree<std::shared_ptr<Pln_Edge>>& theRegister)")
	//			<< "Empty List" << endl
	//			<< abort(FatalError);
	//	}

	//	std::vector<std::shared_ptr<Pln_Edge>> list;

	//	std::shared_ptr<Pln_Edge> edge;
	//	theRegister.Root(edge);
	//	theRegister.Remove(edge);

	//	if (edge->IsRing())
	//	{
	//		list.push_back(edge);
	//		//theRegister.Remove(edge);

	//		auto compound = Pln_Tools::MakeCompoundEdge(list);

	//		auto wire = std::make_shared<Pln_Wire>(0, compound);
	//		return std::move(wire);
	//	}

	//	const auto vtx = edge->FirstVtx();
	//	auto nextEdge = edge;
	//	list.push_back(nextEdge);

	//	auto nextVtx = retrieveWires::NextNode(vtx, nextEdge);
	//	while (nextVtx NOT_EQUAL vtx)
	//	{
	//		nextEdge = retrieveWires::NextEdge(nextEdge, nextVtx);

	//		theRegister.Remove(nextEdge);
	//		list.push_back(nextEdge);

	//		nextVtx = retrieveWires::NextNode(nextVtx, nextEdge);
	//	}

	//	auto compound = Pln_Tools::MakeCompoundEdge(list);

	//	Pln_Tools::SameSense(compound);

	//	auto wire = std::make_shared<Pln_Wire>(0, compound);
	//	return std::move(wire);
	//}
}

std::vector<std::shared_ptr<tnbLib::Pln_Wire>> 
tnbLib::Pln_Tools::RetrieveWires
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	if (theEdges.empty())
	{
		return {};
	}
	auto comp = [](const std::shared_ptr<Pln_Edge>& e0, const std::shared_ptr<Pln_Edge>& e1)
	{
		return Pln_Edge::IsLess(e0, e1);
	};
	std::set<std::shared_ptr<Pln_Edge>, decltype(comp)> tank(comp);
	std::for_each(theEdges.begin(), theEdges.end(), [&tank](const std::shared_ptr<Pln_Edge>& edge)
		{
			tank.insert(edge);
		});
	auto track_wire = [&tank]()
	{
		auto current = *tank.begin();
		tank.erase(current); // remove the current edge from the tank
		// Check if the current is a ring
		if (current->IsRing())
		{// Fantastic! It's already a wire!
			auto wire = std::make_shared<Pln_Wire>(0, Pln_Tools::MakeCompoundEdge({ current }));
			return std::move(wire);
		}
		std::vector<std::shared_ptr<Pln_Edge>> l;
		const auto vtx = current->FirstVtx();
		auto next = current;
		if (next->FirstVtx() IS_EQUAL next->LastVtx())
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " - degenerated edge has been detected." << endl
				<< abort(FatalError);
		}
		l.emplace_back(next);
		auto next_vtx = retrieveWires::NextNode(vtx, next);
		while (next_vtx NOT_EQUAL vtx)
		{
			next = retrieveWires::NextEdge(next, next_vtx);
			if (next->FirstVtx() IS_EQUAL next->LastVtx())
			{
				FatalErrorIn(FunctionSIG) << endl
					<< " - degenerated edge has been detected." << endl
					<< abort(FatalError);
			}
			tank.erase(next); // remove the current edge from the tank
			l.emplace_back(next);
			next_vtx = retrieveWires::NextNode(next_vtx, next);
		}
		auto compound = Pln_Tools::MakeCompoundEdge(l);
		Pln_Tools::SameSense(compound);
		return std::make_shared<Pln_Wire>(0, std::move(compound));
	};
	std::vector<std::shared_ptr<Pln_Wire>> wires;
	while(tank.size())
	{
		auto wire = track_wire();
		Debug_Null_Pointer(wire);
		wires.emplace_back(wire);
		wire->SetIndex(wires.size());
	}
	return std::move(wires);
	/*Adt_AvlTree<std::shared_ptr<Pln_Edge>> Register;
	Register.SetComparableFunction(&Pln_Edge::IsLess);

	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		Register.Insert(x);
	}

	while (true)
	{
		auto wire = TrackWire(Register);
		Debug_Null_Pointer(wire);

		list.push_back(std::move(wire));
		if (Register.IsEmpty())
		{
			break;
		}
	}

	Standard_Integer K = 0;
	for (auto& x : list)
	{
		x->SetIndex(++K);
	}
	return std::move(list);*/
}

std::vector<std::shared_ptr<tnbLib::Pln_Wire>> 
tnbLib::Pln_Tools::RetrieveWiresNonManifold
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
	const Standard_Boolean checkManifold,
	const Standard_Integer verbose
)
{
	if (verbose > 1)
	{
		Info << " - calling the function: " << FunctionSIG << endl;
	}

	if (verbose)
	{
		Info << " - checking manifold: " << (checkManifold ? "TRUE": "FALSE") << endl;
	}

	if (checkManifold)
	{
		if (IsManifold(theEdges))
		{
			/*auto cmpEdge = std::make_shared<Pln_CmpEdge>();
			Debug_Null_Pointer(cmpEdge);

			for (const auto& e : theEdges)
			{
				cmpEdge->Insert(e);
			}

			SameSense(cmpEdge);

			auto wire = std::make_shared<Pln_Wire>(std::move(cmpEdge));
			Debug_Null_Pointer(wire);

			std::vector<std::shared_ptr<Pln_Wire>> l;
			l.push_back(std::move(wire));

			return std::move(l);*/

			if (verbose)
			{
				Info << " - the edges are manifold: retrieving the wires..." << endl;
			}

			auto wires = RetrieveWires(theEdges);
			return std::move(wires);
		}
		else
		{
			if (verbose)
			{
				Info << " - the edges are not manifold: recalling the function..." << endl;
			}

			auto wires = RetrieveWiresNonManifold(theEdges, Standard_False);
			return std::move(wires);
		}
	}

	if (verbose)
	{
		Info << " - removing the non-manifold edges..." << endl;
	}
	const auto alg = std::make_shared<Cad2d_RemoveNonManifold>(theEdges);
	Debug_Null_Pointer(alg);
	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not perfomed!");

	const auto rings = alg->RetrieveRings();
	if (rings.empty())
	{
		return {};
	}

	std::vector<std::shared_ptr<Pln_Wire>> l;
	for (const auto& x : rings)
	{
		Debug_Null_Pointer(x);
		auto edges = x->RetrieveEdges();

		auto cmpEdge = std::make_shared<Pln_CmpEdge>();
		Debug_Null_Pointer(cmpEdge);

		for (auto& e : edges)
		{
			cmpEdge->Insert(std::move(e));
		}

		/*auto wires = RetrieveWires(theEdges);*/
		SameSense(cmpEdge);
		
		auto wire = std::make_shared<Pln_Wire>(std::move(cmpEdge));
		Debug_Null_Pointer(wire);

		wire->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);

		l.push_back(std::move(wire));
	}

	if (verbose > 1)
	{
		Info << "leaving the function: " << FunctionSIG << endl;
	}

	return std::move(l);
}