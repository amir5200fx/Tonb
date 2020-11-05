#include <SectPx_oneParFieldFun.hxx>

#include <SectPx_Par.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_oneParFieldFun)
{
	ar & boost::serialization::base_object<SectPx_FieldFun>(*this);
	ar & thePar_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_oneParFieldFun)
{
	ar & boost::serialization::base_object<SectPx_FieldFun>(*this);
	ar & thePar_;
}