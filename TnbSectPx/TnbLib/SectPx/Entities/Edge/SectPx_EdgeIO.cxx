#include <SectPx_Edge.hxx>

#include <SectPx_Pnt.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Edge)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theP0_;
	ar & theP1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Edge)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theP0_;
	ar & theP1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_Edge);