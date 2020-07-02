#include <StbGMaker_SailCreator.hxx>

#include <Marine_Shapes.hxx>
#include <Geo_xDistb.hxx>

tnbLib::StbGMaker_SailCreator::StbGMaker_SailCreator
(
	const Standard_Integer theIndex,
	const word & theName
)
	: StbGMaker_Alg(theIndex, theName)
{
}

tnbLib::StbGMaker_SailCreator::StbGMaker_SailCreator
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<marineLib::Shape_Sail>& theSail
)
	: StbGMaker_Alg(theIndex)
	, theSail_(theSail)
{
}

tnbLib::StbGMaker_SailCreator::StbGMaker_SailCreator
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<marineLib::Shape_Sail>& theSail
)
	: StbGMaker_Alg(theIndex, theName)
	, theSail_(theSail)
{
}

Standard_Integer 
tnbLib::StbGMaker_SailCreator::CreateWorkingPlane
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