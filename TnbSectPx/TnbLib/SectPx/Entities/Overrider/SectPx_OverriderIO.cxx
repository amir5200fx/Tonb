#include <SectPx_Overrider.hxx>

#include <SectPx_MasterPnt.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Overrider)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & thePnt_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Overrider)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & thePnt_;
}