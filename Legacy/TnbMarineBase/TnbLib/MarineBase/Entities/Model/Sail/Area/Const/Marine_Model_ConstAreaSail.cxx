#include <Marine_Model_ConstAreaSail.hxx>

tnbLib::marineLib::Model_ConstAreaSail::Model_ConstAreaSail
(
	const Standard_Real theArea, 
	const Standard_Real theZbar
)
	: theArea_(theArea)
	, theZbar_(theZbar)
{
	// empty body
}

tnbLib::marineLib::Model_ConstAreaSail::Model_ConstAreaSail
(
	const Standard_Integer theIndex,
	const Standard_Real theArea,
	const Standard_Real theZbar
)
	: theArea_(theArea)
	, theZbar_(theZbar)
	, Model_AreaSail(theIndex)
{
	// empty body
}

tnbLib::marineLib::Model_ConstAreaSail::Model_ConstAreaSail
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Standard_Real theArea,
	const Standard_Real theZbar
)
	: theArea_(theArea)
	, theZbar_(theZbar)
	, Model_AreaSail(theIndex, theName)
{
	// empty body
}