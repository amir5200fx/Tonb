#include <StbGMaker_TankCreator.hxx>

#include <Geo_xDistb.hxx>
#include <Marine_Shapes.hxx>

tnbLib::StbGMaker_TankCreator::StbGMaker_TankCreator
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: StbGMaker_Alg(theIndex, theName)
{
}

tnbLib::StbGMaker_TankCreator::StbGMaker_TankCreator
(
	const Standard_Integer theIndex,
	const std::shared_ptr<marineLib::Shape_Tank>& theTank
)
	: StbGMaker_Alg(theIndex)
	, theTank_(theTank)
{
}

tnbLib::StbGMaker_TankCreator::StbGMaker_TankCreator
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<marineLib::Shape_Tank>& theTank
)
	: StbGMaker_Alg(theIndex, theName)
	, theTank_(theTank)
{
}

Standard_Integer 
tnbLib::StbGMaker_TankCreator::CreateWorkingPlane
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