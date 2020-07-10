#include <Marine_Model_ConstAreaSail.hxx>

tnbLib::marineLib::Model_ConstAreaSail::Model_ConstAreaSail
(
	const Standard_Real theArea,
	const Pnt2d & theCentre
)
	: Marine_AreaSailModel(theCentre)
	, theArea_(theArea)
{
}

tnbLib::marineLib::Model_ConstAreaSail::Model_ConstAreaSail
(
	const Standard_Real theArea,
	Pnt2d && theCentre
)
	: Marine_AreaSailModel(std::move(theCentre))
	, theArea_(theArea)
{
}

tnbLib::marineLib::Model_ConstAreaSail::Model_ConstAreaSail
(
	const Standard_Integer theIndex,
	const Standard_Real theArea,
	const Pnt2d & theCentre
)
	: Marine_AreaSailModel(theIndex, theCentre)
	, theArea_(theArea)
{
}

tnbLib::marineLib::Model_ConstAreaSail::Model_ConstAreaSail
(
	const Standard_Integer theIndex, 
	const Standard_Real theArea,
	Pnt2d && theCentre
)
	: Marine_AreaSailModel(theIndex, std::move(theCentre))
	, theArea_(theArea)
{
}

tnbLib::marineLib::Model_ConstAreaSail::Model_ConstAreaSail
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Standard_Real theArea, 
	const Pnt2d & theCentre
)
	: Marine_AreaSailModel(theIndex, theName, theCentre)
	, theArea_(theArea)
{
}

tnbLib::marineLib::Model_ConstAreaSail::Model_ConstAreaSail
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Standard_Real theArea,
	Pnt2d && theCentre
)
	: Marine_AreaSailModel(theIndex, theName, std::move(theCentre))
	, theArea_(theArea)
{
}