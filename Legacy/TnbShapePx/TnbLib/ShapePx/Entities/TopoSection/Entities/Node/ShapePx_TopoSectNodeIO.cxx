#include <ShapePx_TopoSectNode.hxx>

#include <ShapePx_TopoSectPole_Bnd.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_TopoSectNode)
{
	ar & boost::serialization::base_object<ShapePx_TopoSectEntity>(*this);
	ar & boost::serialization::base_object<ShapePx_TopoSectNodeAdaptor>(*this);

	ar & thePole_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_TopoSectNode)
{
	ar & boost::serialization::base_object<ShapePx_TopoSectEntity>(*this);
	ar & boost::serialization::base_object<ShapePx_TopoSectNodeAdaptor>(*this);

	ar & thePole_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::ShapePx_TopoSectNode);