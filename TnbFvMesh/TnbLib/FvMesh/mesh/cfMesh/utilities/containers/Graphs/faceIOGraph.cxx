#include <faceIOGraph.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	faceIOGraph::faceIOGraph(const IOobject& io)
		:
		regIOobject(io),
		VRWGraph()
	{}

	faceIOGraph::faceIOGraph
	(
		const IOobject& io,
		const label size
	)
		:
		regIOobject(io),
		VRWGraph(size)
	{}

	faceIOGraph::faceIOGraph
	(
		const IOobject& io,
		const VRWGraph& g
	)
		:
		regIOobject(io),
		VRWGraph(g)
	{}

	void faceIOGraph::operator=(const faceIOGraph& rhs)
	{
		VRWGraph::operator=(rhs);
	}

	void faceIOGraph::operator=(const VRWGraph& rhs)
	{
		VRWGraph::operator=(rhs);
	}

	bool faceIOGraph::writeData(Ostream& os) const
	{
		return (os << *this).good();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameWithName(faceIOGraph, "faceList");

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //