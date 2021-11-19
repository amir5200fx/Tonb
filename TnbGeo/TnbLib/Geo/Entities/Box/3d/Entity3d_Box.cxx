#include <Entity3d_Box.hxx>

const std::string tnbLib::Entity3d_Box::extension = ".gbox3d";

namespace tnbLib
{

	template<>
	template<>
	Entity3d_Box Entity3d_Box::SubDivide<Box3d_SubDivideAlgorithm>(const Box3d_SubDivideAlgorithm theAlg) const
	{
		switch (theAlg)
		{
		case Box3d_SubDivideAlgorithm_Half_Down:
			return Entity_Box<Pnt3d>(P0(), MEAN(Corner(Box3d_PickAlgorithm_Fwd_SE), Corner(Box3d_PickAlgorithm_Fwd_NE)));

		case Box3d_SubDivideAlgorithm_Half_Up:
			return Entity_Box<Pnt3d>(MEAN(Corner(Box3d_PickAlgorithm_Aft_SW), Corner(Box3d_PickAlgorithm_Aft_NW)), P1());

		case Box3d_SubDivideAlgorithm_Half_Left:
			return Entity_Box<Pnt3d>(P0(), MEAN(Corner(Box3d_PickAlgorithm_Fwd_NW), Corner(Box3d_PickAlgorithm_Fwd_NE)));

		case Box3d_SubDivideAlgorithm_Half_Right:
			return Entity_Box<Pnt3d>(MEAN(Corner(Box3d_PickAlgorithm_Aft_SW), Corner(Box3d_PickAlgorithm_Aft_SE)), P1());

		case Box3d_SubDivideAlgorithm_Half_Aft:
			return Entity_Box<Pnt3d>(P0(), MEAN(Corner(Box3d_PickAlgorithm_Aft_NE), Corner(Box3d_PickAlgorithm_Fwd_NE)));

		case Box3d_SubDivideAlgorithm_Half_Fwd:
			return Entity_Box<Pnt3d>(MEAN(Corner(Box3d_PickAlgorithm_Aft_SW), Corner(Box3d_PickAlgorithm_Fwd_SW)), P1());

		case Box3d_SubDivideAlgorithm_Aft_SW:
			return Entity_Box<Pnt3d>(P0(), CalcCentre());

		case Box3d_SubDivideAlgorithm_Aft_SE:
			return Entity_Box<Pnt3d>
				(
					MEAN(P0(), Corner(Box3d_PickAlgorithm_Aft_SE)),
					MEAN(P1(), Corner(Box3d_PickAlgorithm_Aft_SE))
					);

		case Box3d_SubDivideAlgorithm_Aft_NE:
			return Entity_Box<Pnt3d>
				(
					MEAN(P0(), Corner(Box3d_PickAlgorithm_Aft_NE)),
					MEAN(P1(), Corner(Box3d_PickAlgorithm_Aft_NE))
					);

		case Box3d_SubDivideAlgorithm_Aft_NW:
			return Entity_Box<Pnt3d>
				(
					MEAN(P0(), Corner(Box3d_PickAlgorithm_Aft_NW)),
					MEAN(P1(), Corner(Box3d_PickAlgorithm_Aft_NW))
					);

		case Box3d_SubDivideAlgorithm_Fwd_SW:
			return Entity_Box<Pnt3d>
				(
					MEAN(P0(), Corner(Box3d_PickAlgorithm_Fwd_SW)),
					MEAN(P1(), Corner(Box3d_PickAlgorithm_Fwd_SW))
					);

		case Box3d_SubDivideAlgorithm_Fwd_SE:
			return Entity_Box<Pnt3d>
				(
					MEAN(P0(), Corner(Box3d_PickAlgorithm_Fwd_SE)),
					MEAN(P1(), Corner(Box3d_PickAlgorithm_Fwd_SE))
					);

		case Box3d_SubDivideAlgorithm_Fwd_NE:
			return Entity_Box<Pnt3d>(CalcCentre(), P1());

		case Box3d_SubDivideAlgorithm_Fwd_NW:
			return Entity_Box<Pnt3d>
				(
					MEAN(P0(), Corner(Box3d_PickAlgorithm_Fwd_NW)),
					MEAN(P1(), Corner(Box3d_PickAlgorithm_Fwd_NW))
					);
		}

		return Entity_Box<Pnt3d>();
	}
}