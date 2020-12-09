#include <Marine_Model_SurfaceSail.hxx> 

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	const TopoDS_Face & theFace
)
	: theFace_(theFace)
{
}

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	TopoDS_Face && theFace
)
	: theFace_(std::move(theFace))
{
}

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	const Standard_Integer theIndex,
	const TopoDS_Face & theFace
)
	: Model_PlnSail(theIndex)
	, theFace_(theFace)
{
}

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	const Standard_Integer theIndex, 
	TopoDS_Face && theFace
)
	: Model_PlnSail(theIndex)
	, theFace_(std::move(theFace))
{
}

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	const Standard_Integer theIndex, 
	const word & theName,
	const TopoDS_Face & theFace
)
	: Model_PlnSail(theIndex, theName)
	, theFace_(theFace)
{
}

tnbLib::marineLib::Model_SurfaceSail::Model_SurfaceSail
(
	const Standard_Integer theIndex, 
	const word & theName,
	TopoDS_Face && theFace
)
	: Model_PlnSail(theIndex, theName)
	, theFace_(std::move(theFace))
{
}