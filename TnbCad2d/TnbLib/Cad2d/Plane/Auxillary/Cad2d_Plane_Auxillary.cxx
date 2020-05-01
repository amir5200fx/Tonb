#include <Cad2d_Plane_Auxillary.hxx>

tnbLib::cad2dLib::Plane_Auxillary::Plane_Auxillary
(
	const gp_Ax2 & theSystem
)
	: theSystem_(theSystem)
{
}

tnbLib::cad2dLib::Plane_Auxillary::Plane_Auxillary
(
	const gp_Ax2 && theSystem
)
	: theSystem_(std::move(theSystem))
{
}

void tnbLib::cad2dLib::Plane_Auxillary::SetBoundingBox
(
	const std::shared_ptr<Entity2d_Box> && theB
)
{
	theBoundingBox_ = std::move(theB);
}