#include <SectPx_Node.hxx>

#include <SectPx_Pnt.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_Node)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & boost::serialization::base_object<SectPx_NodeAdaptor>(*this);

	ar & thePnt_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_Node)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & boost::serialization::base_object<SectPx_NodeAdaptor>(*this);

	ar & thePnt_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_Node);