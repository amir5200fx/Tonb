#include <SectPx_Frame.hxx>

#include <SectPx_Registry.hxx>
#include <SectPx_Makers.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Frame::EntityMaker)
{
	ar & Par;
	ar & Pnt;
	ar & GeoMap;
	ar & CmptProfile;
	ar & FieldFun;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Frame::EntityMaker)
{
	ar & Par;
	ar & Pnt;
	ar & GeoMap;
	ar & CmptProfile;
	ar & FieldFun;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Frame)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theRegistry_;
	ar & theMakers_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Frame)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theRegistry_;
	ar & theMakers_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_Frame);