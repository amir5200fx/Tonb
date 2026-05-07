#include <Marine_CmpSection.hxx>

#include <Marine_Section.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_CmpSection)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & Sections();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_CmpSection)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & ChangeSections();
}

void tnbLib::Marine_CmpSection::Save(TNB_oARCH_TYPE& ar, const std::shared_ptr<Marine_CmpSection>& theSection)
{
	ar & theSection;
}

void tnbLib::Marine_CmpSection::Load(TNB_iARCH_TYPE& ar, std::shared_ptr<Marine_CmpSection>& theSection)
{
	ar & theSection;
}