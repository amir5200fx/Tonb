#include <SectPx_ProfileQ.hxx>

#include <SectPx_Pnt.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_ProfileQ)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theQ_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_ProfileQ)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theQ_;
}