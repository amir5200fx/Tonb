#include <Marine_Body_Wetted.hxx>

#include <Marine_CmpSection.hxx>
#include <Marine_Body_Displacer.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Body_Wetted)
{
	ar & boost::serialization::base_object<Marine_HullBody>(*this);
	ar & theMid_;
	ar & theDisplacer_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Body_Wetted)
{
	ar & boost::serialization::base_object<Marine_HullBody>(*this);
	ar & theMid_;
	ar & theDisplacer_;
}

#include <Marine_Shape.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Wetted>)
{
	ar & boost::serialization::base_object<Body_Wetted>(*this);

	ar & theShape_;
	ar & IsSymmetric_;
	ar & theWater_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Wetted>)
{
	ar & boost::serialization::base_object<Body_Wetted>(*this);
	ar & theShape_;
	ar & IsSymmetric_;
	ar & theWater_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_noShape<tnbLib::marineLib::Body_Wetted>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Wetted>);
