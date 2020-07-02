#include <StbGMaker_HullCreator.hxx>

#include <Geo_xDistb.hxx>
#include <Marine_Shapes.hxx>

tnbLib::StbGMaker_HullCreator::StbGMaker_HullCreator
(
	const Standard_Integer theIndex,
	const word & theName
)
	: StbGMaker_Alg(theIndex, theName)
{
}

tnbLib::StbGMaker_HullCreator::StbGMaker_HullCreator
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<marineLib::Shape_Hull>& theHull
)
	: StbGMaker_Alg(theIndex)
	, theHull_(theHull)
{
}

tnbLib::StbGMaker_HullCreator::StbGMaker_HullCreator
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<marineLib::Shape_Hull>& theHull
)
	: StbGMaker_Alg(theIndex, theName)
	, theHull_(theHull)
{
}

Standard_Integer 
tnbLib::StbGMaker_HullCreator::CreateWorkingPlane
(
	const Standard_Real x
)
{
	if (Shape())
	{
		return CreateWpFromShape(Shape()->Shape(), x);
	}
	else
	{
		return StbGMaker_Alg::CreateWorkingPlane(x);
	}
}