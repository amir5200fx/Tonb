#include <SectPx_Interface.hxx>

#include <SectPx_Node.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Interface)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theNode_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Interface)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theNode_;
}