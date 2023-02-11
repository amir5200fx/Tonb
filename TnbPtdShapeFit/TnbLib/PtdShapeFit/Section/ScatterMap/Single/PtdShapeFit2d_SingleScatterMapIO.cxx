#include <PtdShapeFit2d_SingleScatterMap.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdShapeFit2d_SingleScatterMap)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_ScatterMap>(*this);
	ar& thePnts_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdShapeFit2d_SingleScatterMap)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_ScatterMap>(*this);
	ar& thePnts_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdShapeFit2d_SingleScatterMap);