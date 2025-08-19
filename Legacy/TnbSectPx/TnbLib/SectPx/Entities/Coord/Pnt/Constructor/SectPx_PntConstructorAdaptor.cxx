#include <SectPx_PntConstructorAdaptor.hxx>

#include <SectPx_Node.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_PntConstructorAdaptor)
{
	ar & theNode_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_PntConstructorAdaptor)
{
	ar & theNode_;
}