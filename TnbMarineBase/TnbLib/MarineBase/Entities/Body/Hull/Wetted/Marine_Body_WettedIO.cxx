#include <Marine_Body_Wetted.hxx>

#include <Marine_CmpSection.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Body_Wetted)
{
	ar & boost::serialization::base_object<Marine_HullBody>(*this);
	ar & Mid();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Body_Wetted)
{
	ar & boost::serialization::base_object<Marine_HullBody>(*this);
	ar & ChangeMid();
}

#include <Marine_Shape.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Wetted>)
{
	ar & boost::serialization::base_object<Body_Wetted>(*this);

	ar & Shape();
	ar & WL();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Wetted>)
{
	ar & boost::serialization::base_object<Body_Wetted>(*this);

	ar & ChangeShape();
	ar & ChangeWL();
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_noShape<tnbLib::marineLib::Body_Wetted>);

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::shapedWettedBody);