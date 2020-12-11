#include <Marine_Body.hxx>

#include <Marine_CmpSection.hxx>
#include <Marine_BaseLine.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_Body)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & theSections_;
	ar & theBase_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_Body)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & theSections_;
	ar & theBase_;
}

void tnbLib::Marine_Body::Save(TNB_oARCH_TYPE & ar, const std::shared_ptr<Marine_Body>& theBody)
{
	ar & theBody;
}

void tnbLib::Marine_Body::Load(TNB_iARCH_TYPE & ar, std::shared_ptr<Marine_Body>& theBody)
{
	ar & theBody;
}