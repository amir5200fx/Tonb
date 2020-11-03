#include <Marine_CmpSection.hxx>

#include <Marine_Section.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_CmpSection)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & Sections();
}

DECLARE_LOAD_IMP(tnbLib::Marine_CmpSection)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & ChangeSections();
}