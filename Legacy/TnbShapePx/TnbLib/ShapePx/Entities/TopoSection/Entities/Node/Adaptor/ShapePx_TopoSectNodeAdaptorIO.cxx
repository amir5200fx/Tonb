#include <ShapePx_TopoSectNodeAdaptor.hxx>

#include <ShapePx_TopoSectProfile.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_TopoSectNodeAdaptor)
{
	ar & theProfile_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_TopoSectNodeAdaptor)
{
	ar & theProfile_;
}