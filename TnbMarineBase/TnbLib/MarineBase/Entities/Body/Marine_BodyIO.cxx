#include <Marine_Body.hxx>

#include <Marine_CmpSection.hxx>
#include <Marine_BaseLine.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_Body)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & Sections();
	ar & BaseLine();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_Body)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & ChangeSections();
	ar & ChangeBaseLine();
}