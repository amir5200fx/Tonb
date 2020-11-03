#include <Marine_Body_Wetted.hxx>

#include <Marine_CmpSection.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::Body_Wetted)
{
	ar & boost::serialization::base_object<Marine_HullBody>(*this);
	ar & Mid();
}

DECLARE_LOAD_IMP(tnbLib::marineLib::Body_Wetted)
{
	ar & boost::serialization::base_object<Marine_HullBody>(*this);
	ar & ChangeMid();
}

#include <Marine_Shape.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Wetted>)
{
	ar & boost::serialization::base_object<Body_Wetted>(*this);

	ar & Shape();
	ar & WL();
}

DECLARE_LOAD_IMP(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Wetted>)
{
	ar & boost::serialization::base_object<Body_Wetted>(*this);

	ar & ChangeShape();
	ar & ChangeWL();
}