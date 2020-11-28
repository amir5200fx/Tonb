#include <SectPx_ProfileQ.hxx>

#include <SectPx_Pnt.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_ProfileQ)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theQ_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_ProfileQ)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theQ_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_ProfileQ);