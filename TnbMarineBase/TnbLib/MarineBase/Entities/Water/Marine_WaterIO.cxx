#include <Marine_Water.hxx>

#include <Marine_Section.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_Water)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);

	ar & theSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_Water)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);

	ar & theSections_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Marine_Water);