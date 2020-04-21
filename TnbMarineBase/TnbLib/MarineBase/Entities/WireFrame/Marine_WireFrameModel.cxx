#include <Marine_WireFrameModel.hxx>

tnbLib::Marine_WireFrameModel::Marine_WireFrameModel()
{
}

tnbLib::Marine_WireFrameModel::Marine_WireFrameModel
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_Entity(theIndex, theName)
{
}