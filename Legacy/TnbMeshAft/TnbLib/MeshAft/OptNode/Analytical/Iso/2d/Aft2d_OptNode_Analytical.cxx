#include <Aft2d_OptNode_Analytical.hxx>

namespace tnbLib
{

	template<>
	void Aft2d_OptNode_Analytical::Perform()
	{
		const auto& edge = Front();
		const auto& middle = edge.Centre();

		auto vec = (edge.Node1()->Coord() - edge.Node0()->Coord()).UnitLength();
		vec.Rotate90ccw();

		ChangeCoord() = middle + ElementSize() * vec;
		Change_IsDone() = Standard_True;
	}
}