#include <ShapePx_TopoSectPole_InterAdaptor.hxx>

#include <ShapePx_TopoSectSegment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::shapePxLib::TopoSectPole_InterAdaptor)
{
	ar & theBackward_;
	ar & theForward_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::shapePxLib::TopoSectPole_InterAdaptor)
{
	ar & theBackward_;
	ar & theForward_;
}