#include <Marine_Graph.hxx>

tnbLib::Marine_Graph::Marine_Graph
(
	const Standard_Integer theIndex
)
	: Marine_GraphEntity(theIndex)
{
	//- empty body
}

tnbLib::Marine_Graph::Marine_Graph
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Marine_GraphEntity(theIndex, theName)
{
	//- empty body
}

Standard_Integer 
tnbLib::Marine_Graph::NbCurves() const
{
	return (Standard_Integer)theCurves_.size();
}