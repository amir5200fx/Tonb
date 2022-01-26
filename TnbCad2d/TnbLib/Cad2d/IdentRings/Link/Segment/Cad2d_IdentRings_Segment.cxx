#include <Cad2d_IdentRings_Segment.hxx>

#include <Cad2d_IdentRings_Node.hxx>

void tnbLib::cad2dLib::IdentRings_Segment::Attach()
{
	{
		const auto& node = Node0();
		if (NOT node)
		{
			FatalErrorIn(FunctionSIG)
				<< "no node is attached to the link!" << endl
				<< abort(FatalError);
		}

		if (node->Contains(Index()))
		{
			Info << " the edge already exists in the node registry!" << endl;
		}
		else
		{
			node->Insert(Index(), std::dynamic_pointer_cast<IdentRings_Segment>(This()));
		}
	}

	{
		const auto& node = Node1();
		if (NOT node)
		{
			FatalErrorIn(FunctionSIG)
				<< "no node is attached to the link!" << endl
				<< abort(FatalError);
		}

		if (node->Contains(Index()))
		{
			Info << " the edge already exists in the node registry!" << endl;
		}
		else
		{
			node->Insert(Index(), std::dynamic_pointer_cast<IdentRings_Segment>(This()));
		}
	}
}

void tnbLib::cad2dLib::IdentRings_Segment::Detach()
{
	{
		const auto& node = Node0();
		if (NOT node)
		{
			FatalErrorIn(FunctionSIG)
				<< "no node is attached to the link!" << endl
				<< abort(FatalError);
		}

		node->Remove(Index());
	}

	{
		const auto& node = Node1();
		if (NOT node)
		{
			FatalErrorIn(FunctionSIG)
				<< "no node is attached to the link!" << endl
				<< abort(FatalError);
		}

		node->Remove(Index());
	}
}