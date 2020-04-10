#include <Marine_VesselModel.hxx>

tnbLib::Marine_VesselModel::Marine_VesselModel()
{
}

tnbLib::Marine_VesselModel::Marine_VesselModel
(
	const Standard_Integer theIndex
)
	: Marine_Model(theIndex)
{
}

tnbLib::Marine_VesselModel::Marine_VesselModel
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_Model(theIndex, theName)
{
}