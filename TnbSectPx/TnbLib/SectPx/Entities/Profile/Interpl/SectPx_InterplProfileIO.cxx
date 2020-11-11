#include <SectPx_InterplProfile.hxx>

#include <SectPx_Pnt.hxx>
#include <SectPx_Cloud.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_InterplProfile)
{
	ar & boost::serialization::base_object<SectPx_TopoProfile>(*this);
	ar & thePnts_;
	ar & theCloud_;
	ar & theTol_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_InterplProfile)
{
	ar & boost::serialization::base_object<SectPx_TopoProfile>(*this);
	ar & thePnts_;
	ar & theCloud_;
	ar & theTol_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_InterplProfile);