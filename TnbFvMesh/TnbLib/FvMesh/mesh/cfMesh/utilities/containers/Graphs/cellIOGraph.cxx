#include <cellIOGraph.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	cellIOGraph::cellIOGraph(const IOobject& io)
		:
		regIOobject(io),
		VRWGraph()
	{}

	cellIOGraph::cellIOGraph
	(
		const IOobject& io,
		const label size
	)
		:
		regIOobject(io),
		VRWGraph(size)
	{}

	cellIOGraph::cellIOGraph
	(
		const IOobject& io,
		const VRWGraph& g
	)
		:
		regIOobject(io),
		VRWGraph(g)
	{}

	void cellIOGraph::operator=(const cellIOGraph& rhs)
	{
		VRWGraph::operator=(rhs);
	}

	void cellIOGraph::operator=(const VRWGraph& rhs)
	{
		VRWGraph::operator=(rhs);
	}

	bool cellIOGraph::writeData(Ostream& os) const
	{
		return (os << *this).good();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameWithName(cellIOGraph, "cellList");

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //