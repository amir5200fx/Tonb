#include <Marine_Body.hxx>

#include <Marine_CmpSection.hxx>
#include <Marine_BaseLine.hxx>
#include <Marine_Bodies.hxx>

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
	if (std::dynamic_pointer_cast<marineLib::Body_Wetted>(theBody))
	{
		ar & std::dynamic_pointer_cast<marineLib::Body_Wetted>(theBody);
		return;
	}
	ar & theBody;
}

void tnbLib::Marine_Body::Load(TNB_iARCH_TYPE & ar, std::shared_ptr<Marine_Body>& theBody)
{
	ar & theBody;
}