#include <SectPx_Node.hxx>

#include <SectPx_Pnt.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Node)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & boost::serialization::base_object<SectPx_NodeAdaptor>(*this);

	ar & thePnt_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Node)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & boost::serialization::base_object<SectPx_NodeAdaptor>(*this);

	ar & thePnt_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_Node);