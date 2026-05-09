#include <ShapePx_TopoCtrlNet.hxx>

#include <ShapePx_TopoSection.hxx>
#include <ShapePx_TopoSectSegment.hxx>
#include <ShapePx_TopoSectPole.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_TopoCtrlNet)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);

	ar & theSections_;

	ar & theKnots_;
	ar & theRowDeg_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_TopoCtrlNet)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);

	ar & theSections_;

	ar & theKnots_;
	ar & theRowDeg_;
}


BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::ShapePx_TopoCtrlNet);