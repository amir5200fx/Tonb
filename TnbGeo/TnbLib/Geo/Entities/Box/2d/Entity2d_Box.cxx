#include <Entity2d_Box.hxx>

const std::string tnbLib::Entity2d_Box::extension = ".gbox2d";

namespace tnbLib
{

	template<>
	template<>
	Entity2d_Box Entity2d_Box::SubDivide<Box2d_SubDivideAlgorithm>(const Box2d_SubDivideAlgorithm theAlg) const
	{
		switch (theAlg)
		{
		case Box2d_SubDivideAlgorithm_Half_Down:
			return Entity_Box<Pnt2d>(P0(), MEAN(Corner(Box2d_PickAlgorithm_SE), Corner(Box2d_PickAlgorithm_NE)));

		case Box2d_SubDivideAlgorithm_Half_Up:
			return Entity_Box<Pnt2d>(MEAN(Corner(Box2d_PickAlgorithm_SW), Corner(Box2d_PickAlgorithm_NW)), P1());

		case Box2d_SubDivideAlgorithm_Half_Left:
			return Entity_Box<Pnt2d>(P0(), MEAN(Corner(Box2d_PickAlgorithm_NW), Corner(Box2d_PickAlgorithm_NE)));

		case Box2d_SubDivideAlgorithm_Half_Right:
			return Entity_Box<Pnt2d>(MEAN(Corner(Box2d_PickAlgorithm_SW), Corner(Box2d_PickAlgorithm_SE)), P1());

		case Box2d_SubDivideAlgorithm_Quad_SW:
			return Entity_Box<Pnt2d>(P0(), CalcCentre());

		case Box2d_SubDivideAlgorithm_Quad_SE:
			return Entity_Box<Pnt2d>
				(
					MEAN(Corner(Box2d_PickAlgorithm_SW), Corner(Box2d_PickAlgorithm_SE)),
					MEAN(Corner(Box2d_PickAlgorithm_SE), Corner(Box2d_PickAlgorithm_NE))
					);

		case Box2d_SubDivideAlgorithm_Quad_NE:
			return Entity_Box<Pnt2d>(CalcCentre(), P1());

		case Box2d_SubDivideAlgorithm_Quad_NW:
			return Entity_Box<Pnt2d>
				(
					MEAN(Corner(Box2d_PickAlgorithm_SW), Corner(Box2d_PickAlgorithm_NW)),
					MEAN(Corner(Box2d_PickAlgorithm_NW), Corner(Box2d_PickAlgorithm_NE))
					);
		}

		return Entity_Box<Pnt2d>();
	}

	/*template<>
	template<>
	Pnt2d Entity2d_Box::Corner<Box2d_PickAlgorithm>(const Box2d_PickAlgorithm theAlg) const
	{
		switch (theAlg)
		{
		case Box2d_PickAlgorithm_SW:
			return P0();
		case Box2d_PickAlgorithm_SE:
			return Pnt2d(P1().X(), P0().Y());
		case Box2d_PickAlgorithm_NE:
			return P1();
		case Box2d_PickAlgorithm_NW:
			return Pnt2d(P0().X(), P1().Y());
		}
		return Pnt2d();
	}*/
}