#include <Aft2d_OptNode_Analytical.hxx>

namespace tnbLib
{

	template<>
	void Aft2d_OptNode_Analytical::Perform()
	{
		static const Standard_Real c3 = 0.86602540378443864676372317075294;

		const auto& edge = Front();
		const auto& middle = edge.Centre();

		auto vec = (edge.Node1()->Coord() - edge.Node0()->Coord()).UnitLength();
		vec.Rotate90ccw();

		ChangeCoord() = middle + c3 * ElementSize() * vec;
		Change_IsDone() = Standard_True;
	}
}