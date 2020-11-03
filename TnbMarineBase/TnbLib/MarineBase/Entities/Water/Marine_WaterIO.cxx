#include <Marine_Water.hxx>

#include <Marine_Section.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_Water)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);

	ar & theSections_;
}

DECLARE_LOAD_IMP(tnbLib::Marine_Water)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);

	ar & theSections_;
}