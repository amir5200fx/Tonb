#include <Pln_Wire.hxx>

#include <Adt_AvlTree.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Tools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::Pln_Wire::Reverse()
{
	if (Orientation() IS_EQUAL Pln_Orientation_Unknown)
	{
		FatalErrorIn("void tnbLib::Plane_Wire::Reverse()")
			<< "Unknown orientation"
			<< abort(FatalError);
	}

	theEdges_->Reverse();
	theOrientation_ = tnbLib::Reverse(Orientation());
}

void tnbLib::Pln_Wire::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
) const
{
	theVertices.reserve(NbEdges());
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		theVertices.push_back(x->Vtx0());
	}
}

namespace tnbLib
{
	std::shared_ptr<tnbLib::Pln_Edge>
		Next
		(
			const std::shared_ptr<tnbLib::Pln_Edge>& theEdge
		)
	{
		if (theEdge->IsRing())
		{
			FatalErrorIn("std::shared_ptr<Pln_Edge> Next(const std::shared_ptr<Pln_Edge>& theEdge)")
				<< "Invalid wire: contains at least one ring!" << endl
				<< abort(FatalError);
		}

		const auto& vtx = theEdge->Vtx1();
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

		std::vector<std::weak_ptr<Pln_Edge>> list;
		vtx->RetrieveEdgesTo(list);

		Debug_If_Condition(list.size() NOT_EQUAL 2);

		Debug_Null_Pointer(list[0].lock());
		Debug_Null_Pointer(list[1].lock());

		auto edge0 = list[0].lock();
		auto edge1 = list[1].lock();

		if (edge0 IS_EQUAL theEdge) return edge1;
		else return edge0;
	}

	std::shared_ptr<tnbLib::Pln_Wire>
		TrackWire
		(
			Adt_AvlTree<std::shared_ptr<Pln_Edge>>& theRegister
		)
	{
		if (theRegister.IsEmpty())
		{
			FatalErrorIn("wire_ptr TrackWire(Adt_AvlTree<std::shared_ptr<Pln_Edge>>& theRegister)")
				<< "Empty List" << endl
				<< abort(FatalError);
		}

		auto list = std::make_shared<std::vector<std::shared_ptr<Pln_Edge>>>();

		std::shared_ptr<Pln_Edge> edge;
		theRegister.Root(edge);

		if (edge->IsRing())
		{
			list->push_back(edge);
			theRegister.Remove(edge);

			auto compound = Pln_Tools::MakeCompoundEdge(*list);

			auto wire = std::make_shared<Pln_Wire>(0, compound);
			return std::move(wire);
		}

		auto root = edge;
		list->push_back(edge);

		Standard_Boolean cycle = Standard_False;
		while (NOT theRegister.IsEmpty())
		{
			theRegister.Remove(edge);
			edge = Next(edge);

			if (edge IS_EQUAL root)
			{
				cycle = Standard_True;
				break;
			}
			list->push_back(edge);
		}

		if (NOT cycle)
		{
			FatalErrorIn("wire_ptr TrackWire(Adt_AvlTree<std::shared_ptr<Plane_Edge>>& theRegister)")
				<< "found no wire" << endl
				<< abort(FatalError);
		}

		auto compound = Pln_Tools::MakeCompoundEdge(*list);

		auto wire = std::make_shared<Pln_Wire>(0, compound);

		return std::move(wire);
	}
}

std::vector<std::shared_ptr<tnbLib::Pln_Wire>> 
tnbLib::Pln_Wire::RetrieveWires
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	if (theEdges.empty())
	{
		FatalErrorIn("wireList RetrieveWires()")
			<< "Empty List" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Pln_Wire>> list;

	Adt_AvlTree<std::shared_ptr<Pln_Edge>> Register;
	Register.SetComparableFunction(&Pln_Edge::IsLess);

	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		Register.Insert(x);
	}

	while (true)
	{
		list.push_back(TrackWire(Register));
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
	return std::move(list);
}