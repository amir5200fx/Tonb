#include <Marine_Model_LateralPlnSail.hxx>

tnbLib::marineLib::Model_LateralPlnSail::Model_LateralPlnSail
(
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
	: thePlane_(thePlane)
{
	// empty body
}

tnbLib::marineLib::Model_LateralPlnSail::Model_LateralPlnSail
(
	std::shared_ptr<Cad2d_Plane>&& thePlane
)
	: thePlane_(std::move(thePlane))
{
	// empty body
}

tnbLib::marineLib::Model_LateralPlnSail::Model_LateralPlnSail
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
	: Model_PlnSail(theIndex)
	, thePlane_(thePlane)
{
	// empty body
}

tnbLib::marineLib::Model_LateralPlnSail::Model_LateralPlnSail
(
	const Standard_Integer theIndex, 
	std::shared_ptr<Cad2d_Plane>&& thePlane
)
	: Model_PlnSail(theIndex)
	, thePlane_(std::move(thePlane))
{
	// empty body
}

tnbLib::marineLib::Model_LateralPlnSail::Model_LateralPlnSail
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
	: Model_PlnSail(theIndex, theName)
	, thePlane_(thePlane)
{
	// empty body
}

tnbLib::marineLib::Model_LateralPlnSail::Model_LateralPlnSail
(
	const Standard_Integer theIndex, 
	const word & theName,
	std::shared_ptr<Cad2d_Plane>&& thePlane
)
	: Model_PlnSail(theIndex, theName)
	, thePlane_(std::move(thePlane))
{
	// empty body
}