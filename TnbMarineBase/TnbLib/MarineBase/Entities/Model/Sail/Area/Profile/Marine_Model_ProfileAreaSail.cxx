#include <Marine_Model_ProfileAreaSail.hxx>

tnbLib::marineLib::Model_ProfileAreaSail::Model_ProfileAreaSail
(
	const std::shared_ptr<Geo_ProfileFun>& theFun,
	const Pnt2d & theCentre
)
	: Marine_AreaSailModel(theCentre)
	, theProfile_(theFun)
{
}

tnbLib::marineLib::Model_ProfileAreaSail::Model_ProfileAreaSail
(
	std::shared_ptr<Geo_ProfileFun>&& theFun,
	Pnt2d && theCentre
)
	: Marine_AreaSailModel(std::move(theCentre))
	, theProfile_(std::move(theFun))
{
}

tnbLib::marineLib::Model_ProfileAreaSail::Model_ProfileAreaSail
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<Geo_ProfileFun>& theFun, 
	const Pnt2d & theCentre
)
	: Marine_AreaSailModel(theIndex, theName, theCentre)
	, theProfile_(theFun)
{
}

tnbLib::marineLib::Model_ProfileAreaSail::Model_ProfileAreaSail
(
	const Standard_Integer theIndex, 
	const word & theName,
	std::shared_ptr<Geo_ProfileFun>&& theFun,
	Pnt2d && theCentre
)
	: Marine_AreaSailModel(theIndex, theName, std::move(theCentre))
	, theProfile_(std::move(theFun))
{
}