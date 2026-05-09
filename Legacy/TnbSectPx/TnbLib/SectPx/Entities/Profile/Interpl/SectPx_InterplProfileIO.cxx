#include <SectPx_InterplProfile.hxx>

#include <SectPx_Pnt.hxx>
#include <SectPx_Cloud.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_InterplProfile)
{
	ar & boost::serialization::base_object<SectPx_TopoProfile>(*this);
	ar & thePnts_;
	ar & theCloud_;
	ar & theTol_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_InterplProfile)
{
	ar & boost::serialization::base_object<SectPx_TopoProfile>(*this);
	ar & thePnts_;
	ar & theCloud_;
	ar & theTol_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_InterplProfile);