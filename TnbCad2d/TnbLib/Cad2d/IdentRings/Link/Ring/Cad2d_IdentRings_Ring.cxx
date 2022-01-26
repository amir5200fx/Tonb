#include <Cad2d_IdentRings_Ring.hxx>

#include <Cad2d_IdentRings_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::cad2dLib::IdentRings_Ring::Attach()
{
	const auto& node = Node();
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
		node->Insert(Index(), std::dynamic_pointer_cast<IdentRings_Ring>(This()));
	}
}

void tnbLib::cad2dLib::IdentRings_Ring::Detach()
{
	const auto& node = Node();
	if (NOT node)
	{
		FatalErrorIn(FunctionSIG)
			<< "no node is attached to the link!" << endl
			<< abort(FatalError);
	}

	node->Remove(Index());
}