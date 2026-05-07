#include <ShapePx_TopoSectProfile.hxx>

#include <ShapePx_TopoSectNode.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_TopoSectProfile)
{
	ar & boost::serialization::base_object<ShapePx_TopoSectEntity>(*this);

	ar & thePlane_;

	ar & theNode0_;
	ar & theNode1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_TopoSectProfile)
{
	ar & boost::serialization::base_object<ShapePx_TopoSectEntity>(*this);

	ar & thePlane_;

	ar & theNode0_;
	ar & theNode1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::ShapePx_TopoSectProfile);