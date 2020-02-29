#include <Marine_Graph.hxx>

tnbLib::Marine_Graph::Marine_Graph()
{
}

tnbLib::Marine_Graph::Marine_Graph
(
	const Standard_Integer theIndex
)
	: Marine_GraphEntity(theIndex)
{
}

tnbLib::Marine_Graph::Marine_Graph
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Marine_GraphEntity(theIndex, theName)
{
}

Standard_Integer 
tnbLib::Marine_Graph::NbCurves() const
{
	return (Standard_Integer)theCurves_.size();
}