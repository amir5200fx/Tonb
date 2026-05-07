#include <ShapePx_TopoSectPole_BndAdaptor.hxx>

#include <ShapePx_TopoSectSegment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::shapePxLib::TopoSectPole_BndAdaptor)
{
	ar & theSegment_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::shapePxLib::TopoSectPole_BndAdaptor)
{
	ar & theSegment_;
}