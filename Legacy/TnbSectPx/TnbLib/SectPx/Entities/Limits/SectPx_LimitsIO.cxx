#include <SectPx_Limits.hxx>

#include <SectPx_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Limits)
{
	ar & boost::serialization::base_object<SectPx_Parent>(*this);
	ar & theStart_;
	ar & theEnd_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Limits)
{
	ar & boost::serialization::base_object<SectPx_Parent>(*this);
	ar & theStart_;
	ar & theEnd_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_Limits);