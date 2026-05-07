#include <SectPx_SlavePnt.hxx>

#include <SectPx_MasterPnt.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_SlavePnt)
{
	ar & boost::serialization::base_object<SectPx_TPnt>(*this);
	ar & theMaster_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_SlavePnt)
{
	ar & boost::serialization::base_object<SectPx_TPnt>(*this);
	ar & theMaster_;
}