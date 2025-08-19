#include <ShapePx_TopoSection.hxx>

#include <ShapePx_TopoSectSegment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_TopoSection)
{
	ar & boost::serialization::base_object<ShapePx_TopoSectEntity>(*this);

	ar & theSegments_;
	ar & theX_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_TopoSection)
{
	ar & boost::serialization::base_object<ShapePx_TopoSectEntity>(*this);

	ar & theSegments_;
	ar & theX_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::ShapePx_TopoSection);