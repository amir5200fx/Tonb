#include <SectPx_Interface.hxx>

#include <SectPx_Node.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_Interface)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theNode_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_Interface)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theNode_;
}