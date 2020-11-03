#include <Marine_Body.hxx>

#include <Marine_CmpSection.hxx>
#include <Marine_BaseLine.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_Body)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & Sections();
	ar & BaseLine();
}

DECLARE_LOAD_IMP(tnbLib::Marine_Body)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & ChangeSections();
	ar & ChangeBaseLine();
}