#include <Cad2d_EntityEntityIntersection.hxx>

namespace tnbLib
{

	const Standard_Real Cad2d_EntityEntityIntersection::DEFAULT_TOLERANCE(1.0E-6);
}

tnbLib::Cad2d_EntityEntityIntersection::Cad2d_EntityEntityIntersection()
{
}

tnbLib::Cad2d_EntityEntityIntersection::Cad2d_EntityEntityIntersection
(
	const Standard_Integer theIndex
)
	: Global_Indexed(theIndex)
{
}

tnbLib::Cad2d_EntityEntityIntersection::Cad2d_EntityEntityIntersection
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
{
}