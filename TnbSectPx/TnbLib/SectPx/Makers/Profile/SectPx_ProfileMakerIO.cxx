#include <SectPx_ProfileMaker.hxx>

#include <SectPx_TopoProfile.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::maker::Profile)
{
	ar & boost::serialization::base_object<BasicProfile>(*this);
	//ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theProfile_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::maker::Profile)
{
	ar & boost::serialization::base_object<BasicProfile>(*this);
	//ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theProfile_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::maker::Profile);