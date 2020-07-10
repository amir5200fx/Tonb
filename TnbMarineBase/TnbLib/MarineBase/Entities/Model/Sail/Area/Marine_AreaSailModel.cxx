#include <Marine_AreaSailModel.hxx>

tnbLib::Marine_AreaSailModel::Marine_AreaSailModel
(
	const Standard_Integer theIndex, 
	const Pnt2d & theCentre
)
	: Marine_SailModel(theIndex)
	, theCentre_(theCentre)
{
}

tnbLib::Marine_AreaSailModel::Marine_AreaSailModel
(
	const Standard_Integer theIndex,
	Pnt2d && theCentre
)
	: Marine_SailModel(theIndex)
	, theCentre_(std::move(theCentre))
{
}

tnbLib::Marine_AreaSailModel::Marine_AreaSailModel
(
	const Standard_Integer theIndex,
	const word & theName, 
	const Pnt2d & theCentre
)
	: Marine_SailModel(theIndex, theName)
	, theCentre_(theCentre)
{
}

tnbLib::Marine_AreaSailModel::Marine_AreaSailModel
(
	const Standard_Integer theIndex, 
	const word & theName,
	Pnt2d && theCentre
)
	: Marine_SailModel(theIndex, theName)
	, theCentre_(std::move(theCentre))
{
}