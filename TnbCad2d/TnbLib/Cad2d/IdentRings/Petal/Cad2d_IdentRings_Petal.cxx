#include <Cad2d_IdentRings_Petal.hxx>

#include <Cad2d_IdentRings_Link.hxx>
#include <Cad2d_IdentRings_Segment.hxx>
#include <Cad2d_IdentRings_Ring.hxx>
#include <Cad2d_IdentRings_Node.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Vertex.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static std::shared_ptr<Pln_Wire> RetrieveWire
	(
		const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
		const std::shared_ptr<Pln_Vertex>& theVtx
	)
	{
		// Check the edges if they are valid to create a wire. [2/2/2022 Amir]
		Pln_Tools::CheckWire(theEdges);

		auto wire = Pln_Tools::RetrieveWire(theVtx);
		return std::move(wire);
	}
}

std::shared_ptr<tnbLib::Pln_Wire> 
tnbLib::cad2dLib::IdentRings_Petal::MakeWire
(
	const std::shared_ptr<cad2dLib::IdentRings_Petal>& thePetal
)
{
	Debug_Null_Pointer(thePetal);
	const auto& links = thePetal->Links();

	if (links.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the petal list is empty." << endl
			<< abort(FatalError);
	}

	if (links.size() IS_EQUAL 1)
	{
		// the link must be a ring. [2/1/2022 Amir]
		if (auto x = std::dynamic_pointer_cast<IdentRings_Ring>(links.at(0)))
		{
			Debug_Null_Pointer(x->Node());
			auto wire = RetrieveWire(x->Edges(), x->Node()->Vtx());
			return std::move(wire);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "the link is not a ring." << endl
				<< abort(FatalError);
		}
	}
	else
	{
		// Gathering the sub-edges of the links and putting them into an edge list. [2/2/2022 Amir]
		std::vector<std::shared_ptr<Pln_Edge>> edges;
		for (const auto& x : links)
		{
			Debug_Null_Pointer(x);
			if (auto seg = std::dynamic_pointer_cast<IdentRings_Segment>(x))
			{
				Debug_Null_Pointer(seg);
				for (const auto& e : seg->Edges())
				{
					Debug_Null_Pointer(e);
					edges.push_back(e);
				}
			}
		}

		std::shared_ptr<Pln_Vertex> vtx;
		// Find the vertex [2/2/2022 Amir]
		if (auto x = std::dynamic_pointer_cast<IdentRings_Segment>(links.at(0)))
		{
			Debug_Null_Pointer(x->Node0());
			vtx = x->Node0()->Vtx();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "The link is supposed to be a segment." << endl
				<< abort(FatalError);
		}
		
		Debug_Null_Pointer(vtx);

		// Creating a wire from an edge list. [2/2/2022 Amir]
		auto wire = RetrieveWire(edges, vtx);
		return std::move(wire);
	}
	// shouting up the visual studio [2/3/2022 Amir]
	return nullptr;
}