#include <SectPx_TopoSegment.hxx>

#include <SectPx_BndPole.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_TopoSegment)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & thePole0_;
	ar & thePole1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_TopoSegment)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & thePole0_;
	ar & thePole1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_TopoSegment);