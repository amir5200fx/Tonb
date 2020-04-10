#include <Marine_WireFrameModel.hxx>

tnbLib::Marine_WireFrameModel::Marine_WireFrameModel
(
	const TopoDS_Shape & theShape
)
	: theShape_(theShape)
{
}

tnbLib::Marine_WireFrameModel::Marine_WireFrameModel
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const TopoDS_Shape & theShape
)
	: Marine_Entity(theIndex, theName)
	, theShape_(theShape)
{
}