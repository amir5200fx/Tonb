#include <Marine_Model_SurfaceSail.hxx> 

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	const std::shared_ptr<Cad_Shape> & theFace
)
	: theShape_(theFace)
{
}

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	std::shared_ptr<Cad_Shape> && theFace
)
	: theShape_(std::move(theFace))
{
}

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Cad_Shape> & theFace
)
	: Model_PlnSail(theIndex)
	, theShape_(theFace)
{
}

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	const Standard_Integer theIndex, 
	std::shared_ptr<Cad_Shape> && theFace
)
	: Model_PlnSail(theIndex)
	, theShape_(std::move(theFace))
{
}

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<Cad_Shape> & theFace
)
	: Model_PlnSail(theIndex, theName)
	, theShape_(theFace)
{
}

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	const Standard_Integer theIndex, 
	const word & theName,
	std::shared_ptr<Cad_Shape> && theFace
)
	: Model_PlnSail(theIndex, theName)
	, theShape_(std::move(theFace))
{
}