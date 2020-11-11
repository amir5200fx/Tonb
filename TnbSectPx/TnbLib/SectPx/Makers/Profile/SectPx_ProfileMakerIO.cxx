#include <SectPx_ProfileMaker.hxx>

#include <SectPx_TopoProfile.hxx>

DECLARE_SAVE_IMP(tnbLib::maker::Profile)
{
	ar & boost::serialization::base_object<SectPx_Maker>(*this);
	//ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theProfile_;
}

DECLARE_LOAD_IMP(tnbLib::maker::Profile)
{
	ar & boost::serialization::base_object<SectPx_Maker>(*this);
	//ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theProfile_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::maker::Profile);