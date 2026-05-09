#include <Entity2d_Chain.hxx>

#include <Entity2d_Box.hxx>

const std::string tnbLib::Entity2d_Chain::extension = ".chain2d";

namespace tnbLib
{
	
	template<>
	void Entity2d_Chain::CalcBoundingBox()
	{
		theBoundingBox_ = std::make_shared<Entity2d_Box>(Entity2d_Box::BoundingBoxOf(thePoints_));
	}
}