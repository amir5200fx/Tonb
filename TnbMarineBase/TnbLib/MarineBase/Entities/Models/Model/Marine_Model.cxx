#include <Marine_Model.hxx>

tnbLib::Marine_Model::Marine_Model
(
	const TopoDS_Shape& theShape
)
	: theShape_(theShape)
{}

tnbLib::Marine_Model::Marine_Model
(
	const Standard_Integer theIndex,
	const TopoDS_Shape& theShape
)
	: Marine_Entity(theIndex)
	, theShape_(theShape)
{}

tnbLib::Marine_Model::Marine_Model
(
	const Standard_Integer theIndex,
	const word& theName,
	const TopoDS_Shape& theShape
)
	: Marine_Entity(theIndex, theName)
	, theShape_(theShape)
{}