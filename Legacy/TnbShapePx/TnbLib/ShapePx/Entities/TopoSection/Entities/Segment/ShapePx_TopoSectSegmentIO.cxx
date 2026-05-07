#include <ShapePx_TopoSectSegment.hxx>

#include <ShapePx_TopoSectPole.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_TopoSectSegment)
{
	ar & boost::serialization::base_object<ShapePx_TopoSectEntity>(*this);

	ar & thePole0_;
	ar & thePole1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_TopoSectSegment)
{
	ar & boost::serialization::base_object<ShapePx_TopoSectEntity>(*this);

	ar & thePole0_;
	ar & thePole1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::ShapePx_TopoSectSegment);