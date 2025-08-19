#include <SectPx_ExtrTopoSegment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_ExtrTopoSegment)
{
	ar& boost::serialization::base_object<SectPx_TopoSegment>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_ExtrTopoSegment)
{
	ar& boost::serialization::base_object<SectPx_TopoSegment>(*this);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_ExtrTopoSegment);